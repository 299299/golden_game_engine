#include "Scripts/Utilities/Sample.as"
#include "Scripts/Input.as"

String sceneToLoad = "Data/Scenes/testScene_blendtree.xml";//"Data/Scenes/testScene.xml";
Scene@ scene_;
Node@ cameraNode;
Node@ characterNode;

float yaw = 0.0f;
float pitch = 0.0f;

int cameraMode = 0;
int drawDebugMode = 0;
bool dumpAnimation = true;

AnimatorController@ animController;
HavokAnimator@      animator;

float timeScale = 1.0f;
Array<float> timeScales = { 0.1f, 0.25f, 0.5f, 0.75f, 1.0f, 2.5f, 5.0f, 10.0f};
uint currentTimeScaleIndex = 0;

float cam_radius = 20.0f;
float dumpTime = 0;
String animationString;

Window@ fsmWindow;

void Start()
{
    Print("---------------------- Script Start ----------------------");

    if(graphics != null)
    {
        graphics.sRGB = true;
    }

    script.defaultScriptFile = scriptFile;
    cache.autoReloadResources = true;
    input.mouseVisible = true;

    if(!engine.headless)
    {
        SampleStart();
        CreateInstructions();
        CreateFSMWindow();
    }

    CreateScene();
    
    if(!engine.headless)
    {
        Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
        renderer.viewports[0] = viewport;
    }

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

    CharacterController@ cc = characterNode.GetComponent("CharacterController");
    cc.SetRotationOnly(true);

    UpdateFSMWindow();
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

    Text@ statusText = ui.root.CreateChild("Text", "STS");
    statusText.horizontalAlignment = HA_LEFT;
    statusText.verticalAlignment = VA_TOP;
    statusText.SetPosition(0, 300);
    statusText.SetFont(cache.GetResource("Font", "Fonts/MONACO.TTF"), 15);
    statusText.color = Color(1,0,0);

    Text@ animation_dump_text = ui.root.CreateChild("Text", "ADT");
    animation_dump_text.SetFont(cache.GetResource("Font", "Fonts/MONACO.TTF"), 12);
    animation_dump_text.SetPosition(0, 0);
    animation_dump_text.color = Color(0.0f, 0.0f, 1.0f);
}

void UpdateInstructionText()
{
    Text@ instructionText = ui.root.GetChild("IN");
    String text = "AnimationFSM Viewer ShowCase Of NagaGameEngine timeScale = " + timeScale;
    text += ("\nF1 Toggle Console, F2 Toggle Debug HUD");
    text += ("\nF3 Toggle Debug Mode, F4 Toggle Camera Mode");
    text += ("\nF5 Toggle Dump Animation, F6 Toggle TimeScale");
    text += ("\nE Reset Animation, F Toggle Rotation Only");
    text += ("\nC Toggle RootMotion, Space To Toggle Scene Update");
    instructionText.text = text;
}

void MoveCamera(float timeStep)
{
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
    else if(key == 'C')
    {
        if(!scene_.updateEnabled)
            scene_.Update(1.0f/60.0f);
    }
    else if(key == 'J')
    {
        StartRecord();
    }
    else if(key == 'K')
    {
        StopRecord();
    }
    else if(key == 'L')
    {
        StartReplay(1.0f);
    }
    else if(key == 'M')
    {
        StopReplay();
    }
}

void StartRecord()
{
    animController.StartRecordSnapShot(30);
}

void StopRecord()
{
    animController.StopRecordSnapShort();
}

void StartReplay(float speed)
{
    animController.SetSnapShortPlaySpeed(speed);
    animController.PlaySnapShort(true);
}

void StopReplay()
{
    animController.StopPlaySnapShort();
}

void CreateFSMWindow()
{
    fsmWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/FSMWindow.xml"));
    ui.root.AddChild(fsmWindow);
    fsmWindow.SetSize(200, 400);
    fsmWindow.SetPosition(800, 10);
    fsmWindow.BringToFront();
    fsmWindow.opacity = 0.75f;
}

void UpdateFSMWindow()
{
    UIElement@ transitionsUI = fsmWindow.GetChild("transitions", true);
    UIElement@ parameterUI = fsmWindow.GetChild("parameters", true);

    Array<String>@ transitionNames = animController.GetTransitionNames();
    Array<String>@ parameterNames = animController.GetParameterNames();

    transitionsUI.RemoveAllChildren();
    parameterUI.RemoveAllChildren();

    for(uint i=0; i<transitionNames.length; ++i)
    {
        String transitionName = transitionNames[i];

        Print("add transition " + transitionName);
        Button@ button = transitionsUI.CreateChild("Button", transitionName + "_Button");
        button.layoutMode = LM_VERTICAL;
        button.SetStyleAuto();
        button.vars["TransitionName"] = transitionName;
        SubscribeToEvent(button, "Released", "HandleGUITransition"); 

        Text@ buttonText = button.CreateChild("Text", transitionName + "_Text");
        buttonText.text = transitionName;
        buttonText.textAlignment = HA_CENTER;
        buttonText.SetStyleAuto();

        button.verticalAlignment = VA_TOP;
    }

    for(uint i=0; i<parameterNames.length; ++i)
    {
        String parameterName = parameterNames[i];

        Print("add parameters " + parameterName);
        UIElement@ parent = parameterUI.CreateChild("UIElement", parameterName + "_Parent");
        parent.SetLayout(LM_VERTICAL, 2);
        parent.verticalAlignment = VA_TOP;

        UIElement@ parent1 = parent.CreateChild("UIElement", parameterName + "_Parent");
        parent1.SetLayout(LM_HORIZONTAL, 2);
        parent1.verticalAlignment = VA_TOP;

        Text@ text = parent1.CreateChild("Text", parameterName + "_Text");
        LineEdit@ edit = parent1.CreateChild("LineEdit", parameterName + "_Edit");
        edit.maxHeight = 24;
        edit.text = "0";
        text.SetStyleAuto();
        edit.SetStyleAuto();

        Slider@ slider = parent.CreateChild("Slider", parameterName + "_Slider");
        slider.SetStyleAuto();
        slider.maxHeight = 24;
        slider.verticalAlignment = VA_TOP;
        slider.vars["ParameterName"] = parameterName;
        SubscribeToEvent(slider, "SliderChanged", "HandleParamterSlide");

        Vector2 range = animController.GetParameterRange(ShortStringHash(parameterName));
        Print("param range = " + range.ToString());
        slider.range = range.y - range.x;
        slider.vars["ParameterRange"] = range;
        slider.value = -range.x;

        text.text = parameterName;
    }
}

void HandleGUITransition(StringHash eventType, VariantMap& eventData)
{
    UIElement@ clicked = eventData["Element"].GetUIElement();
    String transitionName = clicked.vars["TransitionName"].GetString();
    animController.FireEvent(ShortStringHash(transitionName));
}

void HandleParamterSlide(StringHash eventType, VariantMap& eventData)
{
    Slider@ slider = eventData["Element"].GetUIElement();
    float newValue = eventData["Value"].GetFloat();

    String paramName = slider.vars["ParameterName"].GetString();
    LineEdit@ edit = fsmWindow.GetChild(paramName + "_Edit", true);
    if(edit is null)
        return;

    Vector2 range = slider.vars["ParameterRange"].GetVector2();
    newValue += range.x;

    edit.text = String(newValue);
    characterNode.vars[paramName] = newValue;
}
