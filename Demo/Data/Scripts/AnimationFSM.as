#include "Scripts/Utilities/Sample.as"
#include "Scripts/Utilities/Input.as"
#include "Scripts/Utilities/AnimationDebug.as"

String sceneToLoad = "Data/Scenes/testScene.xml";
Scene@ scene_;
Node@ cameraNode;
Node@ characterNode;

int drawDebugMode = 0;
bool dumpAnimation = true;

AnimatorController@ animController;

float cam_radius = 20.0f;
float dumpTime = 0;
String animationString;
bool current_pause = false;

float yaw,pitch;

void Start()
{
    Print("---------------------- Script Start ----------------------");

    if(graphics !is null)
    {
        graphics.sRGB = true;
    }

    script.defaultScriptFile = scriptFile;
    cache.autoReloadResources = true;
    input.mouseVisible = true;

    if(!engine.headless)
    {
        SampleStart();
        CreateGUI();
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
    script.defaultScene = scene_;

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
    LocomotionController@ lc = characterNode.GetComponent("LocomotionController");
    if(lc !is null)
        lc.SetRotationOnly(true);

    SetActiveScene(scene_);

    UpdateFSMWindow();
}

void CreateGUI()
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

    Text@ animation_dump_text = ui.root.CreateChild("Text", "ADT");
    animation_dump_text.SetFont(cache.GetResource("Font", "Fonts/MONACO.TTF"), 12);
    animation_dump_text.SetPosition(0, 0);
    animation_dump_text.color = Color(0.0f, 0.0f, 1.0f);

    CreateAnimationControlWindow();
    CreateFSMWindow();
    CreateReplayWindow();
}

void UpdateInstructionText()
{
    Text@ instructionText = ui.root.GetChild("IN");
    String text = "AnimationFSM Viewer ShowCase Of NagaGameEngine timeScale = " + timeScale;
    text += ("\nF1 Toggle Console, F2 Toggle Debug HUD");
    text += ("\nF3 Toggle Debug Mode, F4 Toggle Dump Animation");
    text += ("\nF5 Toggle TimeScale");
    text += ("\nE Reset Animation, F Toggle Rotation Only");
    text += ("\nC Toggle RootMotion, Space To Toggle Scene Update");
    instructionText.text = text;
}

void MoveCamera(float timeStep)
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

void SubscribeToEvents()
{
    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent(scene_, "ScenePostUpdate", "HandleScenePostUpdate");
    SubscribeToEvent("KeyDown", "CustomHandleKeyDown");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("ScreenMode", "HandleScreenMode");
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
        scene_.physicsWorld.DrawDebugGeometry(debug, false);
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
    {
        console.Toggle();
    }
    else if(key == KEY_F2)
    {
        debugHud.ToggleAll();
    }
    else if(key == KEY_F3)
    {
        ++drawDebugMode;
        if(drawDebugMode > 2)
            drawDebugMode = 0;
    }
    else if(key == KEY_F4)
    {
        dumpAnimation = !dumpAnimation;
    }
    else if(key == KEY_F5)
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
        LocomotionController@ cc = characterNode.GetComponent("LocomotionController");
        cc.SetRotationOnly(!cc.IsRotationOnly());
    }
    else if(key == KEY_SPACE)
        scene_.updateEnabled = !scene_.updateEnabled;
    else if(key == 'C')
    {
        if(!scene_.updateEnabled)
            scene_.Update(1.0f/60.0f);
    }
}

void CreateFSMWindow()
{
    Window@ fsmWindow = ui.LoadLayout(cache.GetResource("XMLFile", "UI/FSMWindow.xml"));
    ui.root.AddChild(fsmWindow);
    int w = 200, h = 400;
    fsmWindow.SetSize(w, h);
    fsmWindow.SetPosition(graphics.width - w, graphics.height - h);
    fsmWindow.BringToFront();
    fsmWindow.opacity = 0.75f;
}

void UpdateFSMWindow()
{
    Window@ fsmWindow = ui.root.GetChild("FSMWindow", false);
    if(fsmWindow is null)
        return;

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
    LineEdit@ edit = ui.root.GetChild(paramName + "_Edit", true);
    if(edit is null)
        return;

    Vector2 range = slider.vars["ParameterRange"].GetVector2();
    newValue += range.x;

    edit.text = String(newValue);
    characterNode.vars[paramName] = newValue;
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