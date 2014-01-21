#include "Scripts/Utilities/Sample.as"
#include "Scripts/Input.as"

String sceneToLoad = "Data/Scenes/testScene.xml";
Scene@ scene_;
Node@ cameraNode;
Node@ characterNode;

float yaw = 0.0f;
float pitch = 0.0f;

int cameraMode = 0;
int drawDebugMode = 0;
bool dumpAnimation = true;
bool bWalk = false;

AnimatorController@ animController;
HavokAnimator@      animator;

float timeScale = 1.0f;
Array<float> timeScales = { 0.1f, 0.25f, 0.5f, 0.75f, 1.0f, 2.5f, 5.0f, 10.0f};
uint currentTimeScaleIndex = 0;

float cam_radius = 20.0f;
float dumpTime = 0;

float last_right_foot_z = 0;
String animationString;

String lastConsoleCommand;
bool current_pause = false;


GamePad@ g_gamePad = GamePad();

void Start()
{
    Print("---------------------- Script Start ----------------------");

    if(graphics != null)
    {
        graphics.sRGB = true;
    }

    script.defaultScriptFile = scriptFile;
    // Enable automatic resource reloading
    cache.autoReloadResources = true;
    input.mouseVisible = true;

    if(!engine.headless)
    {
        SampleStart();
        CreateInstructions();
        CreateReplayWindow();
    }
    CreateScene();
    
    if(!engine.headless)
        SetupViewport();

    SubscribeToEvents();
}

void Stop()
{
    Print("---------------------- Script Stop ----------------------");
    @characterNode = null;
    @cameraNode = null;
    ui.Clear();
}

void CreateScene()
{
    scene_ = Scene();

    File loadFile(fileSystem.programDir + sceneToLoad, FILE_READ);
    scene_.LoadXML(loadFile);
    characterNode = scene_.GetChild("monk", true);
    if (characterNode is null)
        return;

    characterNode.rotation = Quaternion(0,0,0);
    characterNode.position = Vector3(0,0,0);
    cameraNode = scene_.CreateChild("Camera");
    cameraNode.CreateComponent("Camera");

    Vector3 cameraPosition = Vector3(20.0f, 10.0f, -20.0f);
    cameraPosition.x = characterNode.position.x;
    cameraNode.position = cameraPosition;
    yaw = cameraNode.rotation.yaw;
    pitch = cameraNode.rotation.pitch;
    cameraNode.LookAt(characterNode.position);

    animController = characterNode.GetComponent("AnimatorController");
    animator = characterNode.GetComponent("HavokAnimator");

    //CharacterController@ cc = characterNode.GetComponent("CharacterController");
    //cc.SetRotationOnly(true);

    SubscribeToEvent(characterNode, "AnimationStateEnter", "HandleAnimationStateEnter");

    /*
    for(uint i=0; i<characterNode.numComponents; ++i)
    {
        Component@ comp = characterNode.components[i];
        String msg;
        comp.SaveJson(msg, true);

        String fName = comp.typeName + ".json";
        File jsonFile;
        jsonFile.Open(fName, FILE_WRITE);
        jsonFile.WriteLine(msg);
        jsonFile.Close();
    }

    engine.Exit();
    */
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text", "IN");
    instructionText.SetFont(cache.GetResource("Font", "Fonts/MONACO.TTF"), 12);
    UpdateInstructionText();

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
    instructionText.color = Color(0.0f, 0.25, 0.75f);

    /*Text@ statusText = ui.root.CreateChild("Text", "STS");
    statusText.horizontalAlignment = HA_LEFT;
    statusText.verticalAlignment = VA_TOP;
    statusText.SetPosition(0, 300);
    statusText.SetFont(cache.GetResource("Font", "Fonts/MONACO.TTF"), 15);
    statusText.color = Color(1,0,0);*/

    Text@ animation_dump_text = ui.root.CreateChild("Text", "ADT");
    animation_dump_text.SetFont(cache.GetResource("Font", "Fonts/MONACO.TTF"), 12);
    animation_dump_text.SetPosition(0, 0);
    animation_dump_text.color = Color(0.0f, 0.0f, 1.0f);


    Window@ window = ui.LoadLayout(cache.GetResource("XMLFile", "UI/AnimationControlWindow.xml"));
    int window_width = 100;
    ui.root.AddChild(window);
    window.position = IntVector2(graphics.width - window_width, 0);
    window.SetFixedSize(window_width, window_width*3);

    SubscribeToEvent(window.GetChild("BUTTON_RECORD", true), "Released", "HandleRecordButton");
    SubscribeToEvent(window.GetChild("BUTTON_REPLAY", true), "Released", "HandleReplayButton");
    SubscribeToEvent(window.GetChild("BUTTON_STOP", true), "Released", "HandleStopButton");
    SubscribeToEvent(window.GetChild("BUTTON_PAUSE", true), "Released", "HandlePauseButton");
}

void UpdateInstructionText()
{
    Text@ instructionText = ui.root.GetChild("IN");
    String text = "Animation ShowCase Of NagaGameEngine timeScale = " + timeScale;
    text += ("\nF1 Toggle Console, F2 Toggle Debug HUD");
    text += ("\nF3 Toggle Debug Mode, F4 Toggle Camera Mode");
    text += ("\nF5 Toggle Dump Animation, F6 Toggle TimeScale");
    text += ("\nE Reset Animation, F Toggle Rotation Only");
    text += ("\nC Toggle RootMotion, Space To Toggle Scene Update");
    text += ("\nG Toggle Walk");
    instructionText.text = text;
}

void SetupViewport()
{
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
    // at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
    // use, but now we just use full screen and default render path configured in the engine command line options
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
    SubscribeToEvent("ScreenMode", "HandleScreenMode");
}

void MoveCamera(float timeStep)
{
    //timeStep /= timeScale;

    //a first person free camera
    if(cameraMode == 0)
    {
        float MOVE_SPEED = 20.0f;
        const float MOUSE_SENSITIVITY = 0.1f;
        if(input.keyDown[KEY_LSHIFT])
            MOVE_SPEED = 200.0f;
        if (input.mouseButtonDown[MOUSEB_RIGHT])
        {
            IntVector2 mouseMove = input.mouseMove;
            if (mouseMove.x != 0 || mouseMove.y != 0)
            {
                yaw += mouseMove.x * 0.2f;
                pitch += mouseMove.y * 0.2f;
                cameraNode.rotation = Quaternion(pitch, yaw, 0);
            }
        }
        if (input.keyDown['W'])
            cameraNode.TranslateRelative(Vector3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * timeStep);
        if (input.keyDown['S'])
            cameraNode.TranslateRelative(Vector3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * timeStep);
        if (input.keyDown['A'])
            cameraNode.TranslateRelative(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
        if (input.keyDown['D'])
            cameraNode.TranslateRelative(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    }
    //a side way look camera
    else if(cameraMode == 1)
    {
        Vector3 dir = Vector3(7.5f, 2, 0);
        cameraNode.position = dir + characterNode.position;
        Vector3 position = characterNode.position;
        position.y = dir.y;
        cameraNode.LookAt(position);
    }
}

void SubscribeToEvents()
{
    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent(scene_, "ScenePostUpdate", "HandleScenePostUpdate");
    SubscribeToEvent("KeyDown", "CustomHandleKeyDown");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
    MoveCamera(timeStep);

    String consoleInput = GetConsoleInput();
    HanldeConsoleInput(consoleInput);

    //if we are replaying
    if(animController.GetDebugState() == 2)
    {
        UpdateReplayWindow();
    }
}

void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    Text@ text = ui.root.GetChild("ADT");
    if(text !is null)
    {
        if(dumpAnimation)
        {
            dumpTime += timeStep;
            const float FIX_DUMP_TIME = 1.0f/60.0f;
            if(dumpTime > FIX_DUMP_TIME)
            {
                animController.Dump(animationString);
                text.text = animationString;
                dumpTime -= FIX_DUMP_TIME;
            } 
        }
        else 
            text.text = "";
    }

    UpdateCharacter(timeStep);
}

void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw viewport debug geometry, which will show eg. drawable bounding boxes and skeleton
    // bones. Note that debug geometry has to be separately requested each frame. Disable depth test so that we can see the
    // bones properly
    DebugRenderer@ debug = scene_.debugRenderer;
    debug.AddNode(characterNode, 2.0f, false);

    //debug.Add2DLine(Vector2(10,10), Vector2(10, 100), Color(1,0,0));
    //debug.Add2DStar(Vector2(50,50), Color(0,1,0), 20);
    //debug.Add2DSquare(Vector2(100,100), Color(0,0,1), 20);


    if (drawDebugMode == 0)
        return;
    else if(drawDebugMode == 1)
        renderer.DrawDebugGeometry(false);
    else if(drawDebugMode == 2)
        scene_.havokPhysicsWorld.DrawDebugGeometry(false);
}

void CustomHandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();
    if(key == KEY_ESC)
    {
        if (!console.visible)
            engine.Exit();
        else
            console.visible = false;
    }
    else if(key == KEY_F1)
      console.Toggle();
    else if(key == KEY_F2)
        debugHud.ToggleAll();
    else if(key == KEY_F3)
    {
        ++drawDebugMode;
        if(drawDebugMode > 2)
            drawDebugMode = 0;
    }
    else if(key == KEY_F4)
    {
        cameraMode ++;
        if(cameraMode > 1)
            cameraMode = 0;
    }
    else if(key == KEY_F5)
        dumpAnimation = !dumpAnimation;
    else if(key == KEY_F6)
    {
         timeScale = timeScales[currentTimeScaleIndex];
        ++currentTimeScaleIndex;
        if(currentTimeScaleIndex >= timeScales.length)
            currentTimeScaleIndex = 0;
        scene_.timeScale = timeScale;
        UpdateInstructionText();
    }
    else if(key == 'E')
    {
        animController.Reset();
        characterNode.worldRotation = Quaternion(0,0,0);
    }
    else if(key == 'F')
    {
        CharacterController@ cc = characterNode.GetComponent("CharacterController");
        cc.SetRotationOnly(!cc.IsRotationOnly());
    }
    else if(key == KEY_SPACE)
        scene_.updateEnabled = !scene_.updateEnabled;
    else if(key == 'G')
        bWalk = !bWalk;
    else if(key == 'C')
    {
        if(!scene_.updateEnabled)
            scene_.Update(1.0f/60.0f);
    }
    else if(key == KEY_F9)
    {
        //engine.DumpMemory();
    }

    else if(key == 'J')
    {
        StartRecord();
    }
    else if(key == 'K')
    {
        StopAnimationDebug();
    }
    else if(key == 'L')
    {
        StartReplay(1.0f);
    }
    else if(key == 'M')
    {
        StartReplay(0.0f);
    }
}

//-- clamps an angle to the rangle of [-PI, PI]
float angleDiff( float diff )
{
    if (diff > 180)
        diff -= 360;
    if (diff < -180) 
        diff += 360;
    return diff;
}

float SelectAnimation(float angle, float slice)
{
    //as 0 --> [-22.5, 22.5] range
    //we should move it a bit.
    angle += 180/slice;
    float anglePerSlice = 360/slice;
    float ret = angle/anglePerSlice;
    if(ret < 0)
        ret += slice;
    return ret;
}

//-- computes the difference between the characters current heading and the
//-- heading the user wants them to go in.
float computeDifference()
{
    //-- if the user is not pushing the stick anywhere return.  
    // this prevents the character from turning while stopping 
    // (which looks bad - like the skid to stop animation)
    if( g_gamePad.m_padMagnitude < 0.5f )
    {
        return 0;
    }

    Vector3 desire_fwd_dir = cameraNode.worldRotation * Vector3(g_gamePad.m_leftStickX, 0, g_gamePad.m_leftStickY);
    Vector3 character_fwd_dir = characterNode.worldRotation * Vector3(0,0,1);
    float desireAngle = Atan2(desire_fwd_dir.z, desire_fwd_dir.x);
    float characterAngle = Atan2(character_fwd_dir.z, character_fwd_dir.x);

    //-- check the difference between the characters current heading and the desired heading from the gamepad
    float rawDiff = desireAngle - characterAngle;
    float ret = -angleDiff( rawDiff);

    String text;
    text += ("\nrawDiff = ") + rawDiff;
    text += ("\ndiff = ") + ret;

    Text@ statusText = ui.root.GetChild("STS");
    if(statusText !is null)
    {
        //statusText.text = text;
    }
    
    return ret;
}

void CheckFootFoward()
{
    if(animator is null)
        return;
    int left_bone_id = animator.GetBoneIndex(StringHash("Character1_LeftLeg")); 
    int right_bone_id = animator.GetBoneIndex(StringHash("Character1_RightLeg"));
    float left_dot = animator.GetDotFromBoneTranslationMS(Vector3(0,0,1), left_bone_id);
    float right_dot = animator.GetDotFromBoneTranslationMS(Vector3(0,0,1), right_bone_id);
    
    bool right_moving_forward = right_dot > last_right_foot_z;
    bool right_is_foward = right_dot > left_dot;
    float left_right_dis = Abs(right_dot - left_dot);
    
    last_right_foot_z = right_dot;
    
    Text@ statusText = ui.root.GetChild("STS");
    if(statusText !is null)
    {
        String footForwardStatusText = right_is_foward ? "Right Foot Forward" : "Left Foot Forward";
        String footMovingStatusText = right_moving_forward ? "Right Foot Moving Forward" : "Right Foot Moving Backward";
        String footDisText = "Left Right Dis: " + String(left_right_dis);
        String curVar = characterNode.vars["SelectRightForward"].ToString();
        statusText.text = footForwardStatusText + "\n" + footMovingStatusText + "\n" +footDisText + "\n var = " + curVar;
    }

   int SelectRightForward = 0;
   if(right_is_foward)
   {
        SelectRightForward = 1;
   }
   else 
   {
       SelectRightForward = 0;
   }
   characterNode.vars["SelectRightForward"] = SelectRightForward;

}

void OnUpdateIdle(float timeStep)
{
    //if the user is pushing the gamepad out of the dead zone start walking or running
    if (g_gamePad.m_padMagnitude > 0.1f && g_gamePad.isLeftStickStationary())
    {
        float characterDifference = computeDifference();
        float animIndex = SelectAnimation(characterDifference, 8.0f);
        characterNode.vars["StandToRunIndex"] = animIndex;
        
        Array<String> run_animations = 
        {
            "monk_stand_to_run_0",
            "monk_stand_to_run_45",
            "monk_stand_to_run_90",
            "monk_stand_to_run_135",
            "monk_stand_to_run_180",
            "monk_stand_to_run_135_mirror",
            "monk_stand_to_run_90_mirror",
            "monk_stand_to_run_45_mirror"
        };
        Array<String> walk_animations = 
        {
            "monk_stand_to_walk_0",
            "monk_stand_to_walk_45",
            "monk_stand_to_walk_90",
            "monk_stand_to_walk_135",
            "monk_stand_to_walk_180",
            "monk_stand_to_walk_135_mirror",
            "monk_stand_to_walk_90_mirror",
            "monk_stand_to_walk_45_mirror"
        };

        if(bWalk)
            Print("set animation = " + walk_animations[animIndex]);
        else
            Print("set animation = " + run_animations[animIndex]);

        if(bWalk)
            animController.FireEvent(ShortStringHash("Walk"), 0);
        else
            animController.FireEvent(ShortStringHash("Go"), 0);
        return;
    }
}

void OnUpdateMoving(float timeStep)
{
    if(g_gamePad.m_padMagnitude < 0.1f && g_gamePad.hasLeftStickBeenStationary(0.1f))
    {
        animController.FireEvent(ShortStringHash("Stop"), 0);
        return;
    }

    // don't try to turn if the character is already turning
    // if is in run turn 180 state
    if(animController.IsStateActive(ShortStringHash("RunTurn180State"), 0))
        return;

    float characterDifference = computeDifference();
    if(characterDifference > 120 && g_gamePad.isLeftStickStationary()) 
    {
        animController.FireEvent(ShortStringHash("Turn180"), 0);
        return;
    }

    float turnSeed = 3.0f;
    characterNode.vars["Direction"] = g_gamePad.m_leftStickX;
    characterNode.Yaw(characterDifference * turnSeed * timeStep);
}

void OnUpdateStandToRun(float timeStep)
{
    if(g_gamePad.m_padMagnitude < 0.5)
        animController.FireEvent(ShortStringHash("Stop"), 0);
    else
        animController.FireEvent(ShortStringHash("Continue"), 0);
}

void UpdateCharacter(float timeStep)
{
    g_gamePad.update(timeStep);
    CheckFootFoward();

    int stateId = animController.GetCurStateId(0);
    switch(stateId)
    {
    case 0:
        OnUpdateIdle(timeStep);
        break;
    case 1:
    case 5:
        OnUpdateMoving(timeStep);
        break;
    case 3:
    case 6:
        OnUpdateStandToRun(timeStep);
        break;
    }
}


void HandleAnimationStateEnter(StringHash eventType, VariantMap& eventData)
{
    int nextStateId = eventData["NextState"].GetInt();
    int lastStateId = eventData["LastState"].GetInt();
    if(lastStateId == 2)
    {
        Print("freeze scene update");
        //scene_.updateEnabled = false;
    }
}


void DumpAnimationFSM()
{
    String dumpText;
    animController.Dump(dumpText);
    Print(dumpText);
}

void DumpTransitions()
{
    Array<String> names = animController.GetTransitionNames();
    for(uint i=0; i<names.length; ++i)
    {
        Print("transition name = " + names[i]);
    }
}

void DumpParameters()
{
    Array<String> names = animController.GetParameterNames();
    for(uint i=0; i<names.length; ++i)
    {
        Print("parameter name = " + names[i]);
    }
}

void HanldeConsoleInput(const String& inputText)
{
    if(inputText.length == 0)
        return;

    String scriptExecute = inputText;
    if(inputText.length == 3)
    {
        uint u1 = inputText.AtUTF8(0);
        uint u2 = inputText.AtUTF8(1);
        uint u3 = inputText.AtUTF8(2);
        if(u1 == 27 && u2 == 91)
        {
            if(u3 == 65 && !lastConsoleCommand.empty)
            {
                //backward search histroy
                scriptExecute = lastConsoleCommand;
            }
        }
    }

    if(script.Execute(scriptExecute))
    {
        lastConsoleCommand = scriptExecute;
    }
}

void StartRecord()
{
    animController.StartRecord(30);
}

void StartReplay(float speed)
{
    animController.SetReplaySpeed(speed);
    animController.StartReplay(true);

    int recordedFrames = animController.GetRecordedFrames();
    ShowReplayWindow(recordedFrames);
}

void StopAnimationDebug()
{
    animController.StopDebug();
    HideReplayWindow();
}

void CreateReplayWindow()
{
    Window@ window = ui.root.CreateChild("Window", "REPLAY");
    window.visible = false;
    window.SetStyleAuto();
    int window_height = 50;
    window.position = IntVector2(0,graphics.height - window_height);
    window.SetFixedSize(graphics.width, window_height);
    window.layoutMode = LM_VERTICAL;

    Text@ text = window.CreateChild("Text","REPLAY_TEXT");
    text.text = "Replay Frame = 0";
    text.SetStyleAuto();

    Slider@ slider = window.CreateChild("Slider", "REPLAY_SLIDER");
    slider.SetStyleAuto();
    SubscribeToEvent(slider, "SliderChanged", "HandleReplaySliderChanged");
}

void UpdateReplayWindow()
{
    Slider@ slider = ui.root.GetChild("REPLAY_SLIDER", true);
    Text@ text = ui.root.GetChild("REPLAY_TEXT", true);

    if(current_pause)
        return;
    slider.value = animController.GetReplayFrame();
    text.text = "Replay Frame = " + String(slider.value);    
}

void ShowReplayWindow(float range)
{
    Slider@ slider = ui.root.GetChild("REPLAY_SLIDER", true);
    slider.range = range;
    Window@ window = ui.root.GetChild("REPLAY", true);
    window.visible = true;
}

void HideReplayWindow()
{
    if(engine.headless)
        return;
    Window@ window = ui.root.GetChild("REPLAY", true);
    window.visible = false;
}

void HandleReplaySliderChanged(StringHash eventType, VariantMap& eventData)
{
    float newValue = eventData["Value"].GetFloat();
    int iFrame = newValue;
    animController.SetReplayFrame(iFrame);

    //Slider@ slider = ui.root.GetChild("REPLAY_SLIDER", true);
    Text@ text = ui.root.GetChild("REPLAY_TEXT", true);
    text.text = "Replay Frame = " + String(iFrame);
}

void HandleRecordButton()
{
    StartRecord();
    HideReplayWindow();
}

void HandleReplayButton()
{
    StartReplay(1.0);
}

void HandlePauseButton()
{
    current_pause = !current_pause;
    animController.SetReplaySpeed(current_pause ? 0.0f : 1.0f);
}

void HandleStopButton()
{
    StopAnimationDebug();
}

void HandleScreenMode()
{
    int window_height = 100;
    Window@ window = ui.root.GetChild("REPLAY", true);
    window.position = IntVector2(0,graphics.height - window_height);
    window.SetFixedSize(graphics.width, window_height);

    Window@ window1 = ui.root.GetChild("WINDOW_CONTROL", true);
    if(window1 is null)
        return;
    int window_width = 100;
    window1.position = IntVector2(graphics.width - window_width, 0);
    window1.SetFixedSize(window_width, window_width*3);
}