#include "Scripts/Utilities/Sample.as"

String sceneToLoad = "Data/Scenes/testScene.xml";
Scene@ scene_;
Node@ cameraNode;
Node@ characterNode;

float yaw = 0.0f;
float pitch = 0.0f;
int cameraMode = 0;
Vector3 lookAtTarget;

int drawDebugMode = 0;
bool dumpAnimation = false;

AnimatorController@ animController;

float timeScale = 1.0f;
Array<float> timeScales = { 0.1f, 0.25f, 0.5f, 0.75f, 1.0f, 2.5f, 5.0f, 10.0f};
uint currentTimeScaleIndex = 0;

float cam_radius = 20.0f;
float dumpTime = 0;
float turn_angle = 0;

class GamePad
{
    float m_padAngle;
    float m_padMagnitude;
    float m_previousLeftStickX;
    float m_previousLeftStickY;
    float m_leftStickX;
    float m_leftStickY;
    float m_leftStickHoldTime;
    float m_rightStickX;
    float m_rightStickY;
    GamePad()
    {
        m_padAngle = 0;
        m_padMagnitude = 0;
        m_previousLeftStickX = 0;
        m_previousLeftStickY = 0;
        m_leftStickX = 0;
        m_leftStickY = 0;
        m_leftStickHoldTime = 0;
        m_rightStickX = 0;
        m_rightStickY = 0;
    }
    bool isLeftStickStationary()
    {
        return (m_leftStickHoldTime > 0.01f);
    }
    bool hasLeftStickBeenStationary(float value )
    {
        return (m_leftStickHoldTime > value);
    }
    void update(float timestep)
    {
        m_previousLeftStickX = m_leftStickX;
        m_previousLeftStickY = m_leftStickY;

        Vector3 leftStick = nagainput.GetLeftStickValue(0);
        Vector3 rightStick = nagainput.GetRightStickValue(0);

        m_leftStickX = Lerp(m_leftStickX, leftStick.x, 0.9f);
        m_leftStickY = Lerp(m_leftStickY, leftStick.y, 0.9f);
        m_rightStickX = Lerp(m_rightStickX, rightStick.x, 0.9f);
        m_rightStickY = Lerp(m_rightStickY, rightStick.y, 0.9f);
    
        m_padAngle = Atan2( m_leftStickY, m_leftStickX);
        m_padMagnitude = leftStick.z;
        
        float diff = (m_previousLeftStickX - m_leftStickX) * (m_previousLeftStickX - m_leftStickX) + (m_previousLeftStickY - m_leftStickY) * (m_previousLeftStickY - m_leftStickY);
        if(diff < 0.1f)      
            m_leftStickHoldTime = m_leftStickHoldTime + timestep;
        else        
            m_leftStickHoldTime = 0; 
    }
};

GamePad@ g_gamePad = GamePad();

void Start()
{
    // Enable automatic resource reloading
    cache.autoReloadResources = true;
    input.mouseVisible = true;

    if(!engine.headless)
    {
        SampleStart();
        CreateInstructions();
    }
    CreateScene();
    SetupViewport();
    SubscribeToEvents();
}

void Stop()
{
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

    characterNode.worldRotation = Quaternion(0,0,0);
    cameraNode = scene_.CreateChild("Camera");
    cameraNode.CreateComponent("Camera");

    cameraNode.position = Vector3(0.0f, 5.0f, 0.0f);

    animController = characterNode.GetComponent("AnimatorController");
    animController.Start();

    //CharacterController@ cc = characterNode.GetComponent("CharacterController");
    //cc.SetApplyMotion(false);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text", "IN");
    instructionText.text = "Animation ShowCase Of NagaGameEngine timeScale = " + timeScale;
    instructionText.SetFont(cache.GetResource("Font", "Fonts/MONACO.TTF"), 15);

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
    instructionText.color = Color(1.0f, 0.0, 0.0f);

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
    animation_dump_text.textEffect = TE_SHADOW;
}

void SetupViewport()
{
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
    // at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
    // use, but now we just use full screen and default render path configured in the engine command line options
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
}

void MoveCamera(float timeStep)
{
    //timeStep /= timeScale;

    if(cameraMode == 0)
    {
        // Do not move if the UI has a focused element (the console)
        if (ui.focusElement !is null)
            return;

        // Movement speed as world units per second
        float MOVE_SPEED = 20.0f;
        // Mouse sensitivity as degrees per pixel
        const float MOUSE_SENSITIVITY = 0.1f;

        if(input.keyDown[KEY_LSHIFT])
            MOVE_SPEED = 200.0f;

        // Rotate camera
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

        // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
        // Use the TranslateRelative() function to move relative to the node's orientation. Alternatively we could
        // multiply the desired direction with the node's orientation quaternion, and use just Translate()
        if (input.keyDown['W'])
            cameraNode.TranslateRelative(Vector3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * timeStep);
        if (input.keyDown['S'])
            cameraNode.TranslateRelative(Vector3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * timeStep);
        if (input.keyDown['A'])
            cameraNode.TranslateRelative(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
        if (input.keyDown['D'])
            cameraNode.TranslateRelative(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    }
    else {
        lookAtTarget = lookAtTarget.Lerp(characterNode.worldPosition, timeStep*10);
        cameraNode.LookAt(lookAtTarget);
        cameraNode.worldPosition = Vector3(0,20,0);
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
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
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
                String msg = animController.Dump();
                text.text = msg;
                dumpTime -= FIX_DUMP_TIME;
            } 
        }
        else 
            text.text = "";
    }
    

    if(!animController.IsStarted())
        animController.Start();

    UpdateInput(timeStep);
}

void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw viewport debug geometry, which will show eg. drawable bounding boxes and skeleton
    // bones. Note that debug geometry has to be separately requested each frame. Disable depth test so that we can see the
    // bones properly
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

    // Close console (if open) or exit when ESC is pressed
    if (key == KEY_ESC)
    {
        if (!console.visible)
        {
            engine.Exit();
        }
        else
        {
            console.visible = false;
        }
    }

    // Toggle console with F1
    else if (key == KEY_F1)
        console.Toggle();

    // Toggle debug HUD with F2
    else if (key == KEY_F2)
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
    {
        dumpAnimation = !dumpAnimation;
    }
    else if(key == KEY_F6)
    {
        timeScale = timeScales[currentTimeScaleIndex];
        ++currentTimeScaleIndex;
        if(currentTimeScaleIndex >= timeScales.length)
            currentTimeScaleIndex = 0;
        scene_.timeScale = timeScale;

        Text@ text = ui.root.GetChild("IN");
        text.text = "Animation ShowCase Of NagaGameEngine timeScale = " + timeScale;
    }
    else if(key == 'E')
    {
        animController.Start();
        characterNode.worldRotation = Quaternion(0,0,0);
    }
}

void UpdateInput(float timeStep)
{
    g_gamePad.update(timeStep);
    int stateId = animController.GetCurStateId(0);

    if(nagainput.IsButtonDown(0, XINPUT_GAMEPAD::A) ||
       input.keyDown['Q'])
    {
        //nagainput.Vibrate(0, 1, 1, 5);
        animController.FireEvent("Test", 0);
    }

    if(input.keyDown['R'])
        animController.FireEvent("Test1", 0);

    //idle
    if(stateId == 0)
    {
        //if the user is pushing the gamepad out of the dead zone start walking or running
        if (g_gamePad.m_padMagnitude > 0.1f && g_gamePad.isLeftStickStationary())
            animController.FireEvent("Go", 0);
    }
    //moving
    else if(stateId == 1)
    {
        if(g_gamePad.m_padMagnitude < 0.1f && g_gamePad.hasLeftStickBeenStationary(0.1f))
        {
            animController.FireEvent("Stop", 0);
            return;
        }
    
        float characterDifference = computeDifference();
        if(characterDifference > 120) 
        {
            animController.FireEvent("Turn180", 0);
            return;
        }

        float turnSeed = 3.0f;
        turn_angle = characterDifference * turnSeed * timeStep;
        characterNode.Yaw(-turn_angle);
    }
}

//-- clamps an angle to the rangle of [-2PI, 2PI]
float angleDiff( float diff )
{
    if (diff > 180)
        diff = diff - 360;
    if (diff < -180) 
        diff = diff + 360;
    return diff;
}

float mapAngle(float angle)
{
    if(angle < 0)
        angle  = angle + 360;
    return angle;
}

//-- computes the difference between the characters current heading and the
//-- heading the user wants them to go in.
float computeDifference()
{
    //-- if the user is not pushing the stick anywhere return.  this prevents the character from turning while stopping (which
    //-- looks bad - like the skid to stop animation)
    Text@ statusText = ui.root.GetChild("STS");

    if( g_gamePad.m_padMagnitude < 0.5f )
    {
        //statusText.text = "";
        return 0;
    }

    Vector3 desire_fwd_dir = cameraNode.worldRotation * Vector3(g_gamePad.m_leftStickX,0,g_gamePad.m_leftStickY);
    Vector3 character_fwd_dir = characterNode.worldRotation * Vector3(0,0,1);
    float desireAngle = Atan2(desire_fwd_dir.z, desire_fwd_dir.x);
    float characterAngle = Atan2(character_fwd_dir.z, character_fwd_dir.x);
    // padAngle = g_gamePad.m_padAngle;

    //-- check the difference between the characters current heading and the desired heading from the gamepad
    float ret = angleDiff( desireAngle - characterAngle);

    String text;
    text = ("desired = ") + desireAngle;
    text += ("\ncharacter = ") + characterAngle;
    //text += ("\npad = ") + padAngle;
    text += ("\ndiff = ") + ret;
    text += ("\nturn angle = ") + turn_angle;
    text += ("\npad x = ") + g_gamePad.m_leftStickX + (" y = ") + g_gamePad.m_leftStickY;

    if(statusText !is null)
    {
        statusText.text = text;
    }
    
    return ret;
}

