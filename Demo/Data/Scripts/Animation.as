#include "Scripts/Utilities/Sample.as"
#include "Scripts/Utilities/Input.as"
#include "Scripts/Utilities/AnimationDebug.as"

String sceneToLoad = "Data/Scenes/testScene_1.xml";
Scene@ scene_;
Node@ cameraNode;
Node@ characterNode;

int cameraMode = 1;
int drawDebugMode = 0;
bool dumpAnimation = false;
bool bWalk = false;

AnimatorController@         animController;
HavokAnimator@              animator;
CharacterController@        characterCC;

float cam_radius = 20.0f;
float dumpTime = 0;

String animationString;
bool current_pause = false;
bool lean_left_right = false;
bool freeze_udpate = false;

float       yaw = 0;
float       pitch = 0;
Vector3     camera_target_offset(0, 2.5f, 0);
Vector3     camera_offset(0,1.0,-10);
Vector3     camera_last_target;
Vector2     camera_pitch_range(0, 60);
float       stand_value = 0.0f;
Vector3     camera_last_position;

GamePad@ g_gamePad = GamePad();

void Start()
{
    Print("---------------------- Script Start ----------------------");

    if(graphics !is null)
    {
        graphics.sRGB = true;
        renderer.hdrRendering = true;
    }

    script.defaultScriptFile = scriptFile;
    // Enable automatic resource reloading
    cache.autoReloadResources = true;
    input.mouseVisible = true;

    if(!engine.headless)
    {
        SampleStart();
        CreateGUI();
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
    @characterCC = null;
    ui.Clear();
}

void CreateScene()
{
    scene_ = Scene();
    script.defaultScene = scene_;
    SetActiveScene(scene_);

    File loadFile(fileSystem.programDir + sceneToLoad, FILE_READ);
    scene_.LoadXML(loadFile);
    characterNode = scene_.GetChild("monk", true);
    if (characterNode is null)
        return;

    cameraNode = scene_.CreateChild("Camera");
    cameraNode.CreateComponent("Camera");

    Vector3 cameraPosition = Vector3(20.0f, 10.0f, -20.0f);
    cameraPosition.x = characterNode.position.x;
    cameraNode.position = cameraPosition;
    cameraNode.LookAt(characterNode.position);

    animController = characterNode.GetComponent("AnimatorController");
    animator = characterNode.GetComponent("HavokAnimator");
    if(animController is null)
    {
        animController = characterNode.children[0].GetComponent("AnimatorController");
    }
    if(animator is null)
    {
        animator = characterNode.children[0].GetComponent("HavokAnimator");
        camera_target_offset.y = 0;
    }
    
    characterCC = characterNode.GetComponent("CharacterController");
    characterCC.Transform(Vector3(0,5,0), Quaternion(0,0,0));
    //cc.SetRotationOnly(true);
    //cc.SetApplyMotion(false);
}

void CreateGUI()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text", "IN");
    instructionText.SetFont(cache.GetResource("Font", "Fonts/font.fnt"), 9);
    UpdateInstructionText();

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
    instructionText.color = Color(0.0f, 0.0, 0.15f);
    instructionText.visible = false;

    Text@ animation_dump_text = ui.root.CreateChild("Text", "ADT");
    animation_dump_text.SetFont(cache.GetResource("Font", "Fonts/font.fnt"), 9);
    animation_dump_text.SetPosition(0, 0);
    animation_dump_text.color = Color(0.0f, 0.0f, 1.0f);

    CreateAnimationControlWindow();
    CreateReplayWindow();

    HandleScreenMode();
}

void UpdateInstructionText()
{
    Text@ instructionText = ui.root.GetChild("IN");
    float timeScale = 1.0f;
    if(script.defaultScene !is null)
        timeScale = script.defaultScene.timeScale;
    String text = "Animation ShowCase Of NagaGameEngine timeScale = " + timeScale;
    text += ("\nF1 Toggle Console, F2 Toggle Debug HUD");
    text += ("\nF3 Toggle Debug Mode, F4 Toggle Camera Mode");
    text += ("\nF5 Toggle Dump Animation, F6 Toggle TimeScale");
    text += ("\nE Reset Animation, F Toggle Rotation Only");
    text += ("\nC Toggle RootMotion, Space To Toggle Scene Update");
    text += ("\nG Toggle Walk, J Toggle Lean Left&Right");
    text += ("\nQ Toggle Freeze update");
    instructionText.text = text;
}

void SetupViewport()
{
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;

    RenderPath@ effectRenderPath = viewport.renderPath.Clone();
    //effectRenderPath.Append(cache.GetResource("XMLFile", "PostProcess/AutoExposure.xml"));
    //effectRenderPath.Append(cache.GetResource("XMLFile", "PostProcess/BloomHDR.xml"));
    //effectRenderPath.Append(cache.GetResource("XMLFile", "PostProcess/Tonemap.xml"));
    effectRenderPath.Append(cache.GetResource("XMLFile", "PostProcess/ColorCorrection.xml"));
    effectRenderPath.Append(cache.GetResource("XMLFile", "PostProcess/EdgeFilter.xml"));
    viewport.renderPath = effectRenderPath;
}


void FPSCamera(float timeStep)
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

void ThirdPersonCamera(float timeStep)
{
    const float camera_follow_speed = 10.0f;
    Vector3 target_pos = characterNode.position + characterNode.rotation * camera_target_offset;

    Quaternion rotation(pitch, yaw, 0);
    Vector3 cam_pos = target_pos + rotation * camera_offset;

    float speed = timeStep * camera_follow_speed;

    camera_last_position = camera_last_position.Lerp(cam_pos, speed);
    cameraNode.worldPosition = camera_last_position;

    camera_last_target = camera_last_target.Lerp(target_pos, speed);
    cameraNode.LookAt(camera_last_target);

    Camera@ cam = cameraNode.GetComponent("Camera");
    Vector3 upDir = cameraNode.worldRotation * Vector3(0,1,0);

    VisualDebugCamera(camera_last_position, 
                      camera_last_target, 
                      upDir, 
                      cam.fov);

    if(g_gamePad.isRightStickInDeadZone())
        return;

    float lookX = g_gamePad.m_rightStickX;
    float lookY = g_gamePad.m_rightStickY;

    const float joyLookDeadZone = 0.05f;
    const float joySensitivity = 1.5f;
    if (lookX < -joyLookDeadZone)
        yaw -= joySensitivity * lookX * lookX;
    if (lookX > joyLookDeadZone)
        yaw += joySensitivity * lookX * lookX;
    if (lookY < -joyLookDeadZone)
        pitch += joySensitivity * lookY * lookY;
    if (lookY > joyLookDeadZone)
        pitch -= joySensitivity * lookY * lookY;

    pitch = Clamp(pitch, camera_pitch_range.x, camera_pitch_range.y);
}

void MoveCamera(float timeStep)
{
    switch(cameraMode)
    {
    case 0:
        FPSCamera(timeStep);
        break;

    case 1:
        ThirdPersonCamera(timeStep);
        break;

    default:
        break;
    }
}

void SubscribeToEvents()
{
    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent(scene_, "ScenePostUpdate", "HandleScenePostUpdate");
    SubscribeToEvent("KeyDown", "CustomHandleKeyDown");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("ScreenMode", "HandleScreenMode");
    SubscribeToEvent(characterNode, "AnimationStateEnter", "HandleAnimationStateEnter");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
    MoveCamera(timeStep);

    String consoleInput = GetConsoleInput();
    HanldeConsoleInput(consoleInput);

    //if we are replaying
    if(animController.GetDebugState() == 2)
        UpdateReplayWindow();
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
    DebugRenderer@ debug = scene_.debugRenderer;
    debug.AddNode(characterNode, 2.0f, false);

    if (drawDebugMode == 0)
        return;
    else if(drawDebugMode == 1)
        renderer.DrawDebugGeometry(false);
    else if(drawDebugMode == 2)
        scene_.havokPhysicsWorld.DrawDebugGeometry(debug, false);
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
        SwitchTimeScale();
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
    {
        scene_.updateEnabled = !scene_.updateEnabled;
    }
    else if(key == 'G')
    {
        bWalk = !bWalk;
    }
    else if(key == 'C')
    {
        if(!scene_.updateEnabled)
            scene_.Update(1.0f/60.0f);
    }
	else if(key == 'J')
	{
		lean_left_right = !lean_left_right;
	}
    else if(key == 'Q')
    {
        freeze_udpate = !freeze_udpate;
    }
    else if(key == KEY_LEFT)
    {
        if(animController.GetDebugState() == 2 && current_pause)
        {
            StepFrame(-1);
        }
    }
    else if(key == KEY_RIGHT)
    {
        if(animController.GetDebugState() == 2 && current_pause)
        {
            StepFrame(1);
        }
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
    float inputX = g_gamePad.m_leftStickX;
    float inputY = g_gamePad.m_leftStickY;
    Vector3 inputDir = Vector3(inputX, 0, inputY);
    
    Vector3 desire_fwd_dir = cameraNode.worldRotation * inputDir;
    desire_fwd_dir.y = 0;

    Vector3 cam_fwd_dir = cameraNode.worldRotation * Vector3(0,0,1);
    cam_fwd_dir.y = 0;

    Vector3 character_fwd_dir = characterNode.worldRotation * Vector3(0,0,1);

    float desireAngle = Atan2(desire_fwd_dir.z, desire_fwd_dir.x);
    float characterAngle = Atan2(character_fwd_dir.z, character_fwd_dir.x);

    //Draw Debugs
    Vector3 pos = characterNode.position;
    pos.y = 2.5f;
    DebugRenderer@ debug = scene_.debugRenderer;
    float debugLen = 1;

    character_fwd_dir.Normalize();
    inputDir.Normalize();
    cam_fwd_dir.Normalize();
    
    debug.AddLine(pos,  character_fwd_dir * debugLen + pos, Color(0,1,0));
    debug.AddLine(pos,  inputDir * debugLen + pos, Color(1,0,0));
    debug.AddLine(pos,  cam_fwd_dir * debugLen + pos, Color(0,0,1));

    if(g_gamePad.isLeftStickInDeadZone())
    {
        return 0;
    }

    return -angleDiff(desireAngle - characterAngle);
}


void OnUpdateIdle(float timeStep)
{
    //if the user is pushing the gamepad out of the dead zone start walking or running
    if (!g_gamePad.isLeftStickInDeadZone() && g_gamePad.isLeftStickStationary())
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
    //-- check if we should return to the idle state
    if(g_gamePad.isLeftStickInDeadZone() && g_gamePad.hasLeftStickBeenStationary(0.1f))
    {
        animController.FireEvent(ShortStringHash("Stop"), 0);
        return;
    }

    // don't try to turn if the character is already turning
    // if is in run turn 180 state
    if(animController.IsStateActive(ShortStringHash("RunTurn180State"), 0))
        return;

    float characterDifference = computeDifference();
    if(characterDifference > 115) 
    {
        animController.FireEvent(ShortStringHash("Turn180"), 0);
        return;
    }

    float turnSeed = 3.0f;
    characterNode.vars["Direction"] = lean_left_right ? g_gamePad.m_leftStickX : 0;
    characterCC.Yaw(characterDifference * turnSeed * timeStep);
}

//logic ran while the character is in the idle to run state
void OnUpdateStandToRun(float timeStep)
{
    //-- check if the user is starting and stoping.  if so stop and do a stutter step
    if(g_gamePad.isLeftStickInDeadZone() && g_gamePad.hasLeftStickBeenStationary(0.1f))
        animController.FireEvent(ShortStringHash("Stop"), 0);
    else
        animController.FireEvent(ShortStringHash("Continue"), 0);
}

void UpdateCharacter(float timeStep)
{
    computeDifference();
    g_gamePad.update(timeStep);
    if(freeze_udpate)
        return;

    characterCC.SetLocomotionState(LOCOMOTION_STAND);

    int stateId = animController.GetCurStateId(0);
    switch(stateId)
    {
    case 0:
        OnUpdateIdle(timeStep);
        stand_value += timeStep;
        break;
    case 1:
    case 5:
        characterCC.SetLocomotionState(LOCOMOTION_MOVE);
        OnUpdateMoving(timeStep);
        stand_value -= timeStep;
        break;
    case 3:
    case 6:
        characterCC.SetLocomotionState(LOCOMOTION_MOVE);
        OnUpdateStandToRun(timeStep);
        break;
    default:
        break;
    }

    stand_value = Clamp(stand_value, 0.0f, 1.0f);
    characterNode.vars["Stand_Value"] = stand_value;
}


void HandleAnimationStateEnter(StringHash eventType, VariantMap& eventData)
{
    int nextStateId = eventData["NextState"].GetInt();
    int lastStateId = eventData["LastState"].GetInt();
    if(lastStateId == 3)
    {
        Print("freeze scene update");
        //scene_.updateEnabled = false;
    }
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
