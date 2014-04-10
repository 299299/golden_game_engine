#include "Scripts/Utilities/Sample.as"
#include "Scripts/Utilities/Grid.as"

Scene@      scene_;
Node@       cameraNode;
Node@       previewNode;
Camera@     camera;
String      sceneToLoad                 = "Data/Scenes/previewScene.xml";
String      nodeStructureText;
String      cameraText;
float       zoomSpeed                   = 1.2f;
float       moveSpeed                   = 1.9f;
float       rotateSpeed                 = 4.0f;
float       yaw                         = 0.0f;
float       pitch                       = 0.0f;
String      sceneResourcePath           = AddTrailingSlash(fileSystem.programDir + "Data");
int         drawDebugMode               = 0;
int         maxDebugMode                = 2;
int         fillMode                    = FILL_SOLID;
Array<Node@>    previewChildNodes;
String      havokExportFolder           = "havok_packages";

String       lastFile;
uint         lastTime = 0;
uint          minTime = 3 * 1000;

void ParseArguments()
{
    Array<String>@ arguments = GetArguments();
    
    for (uint i = 0; i < arguments.length; ++i)
    {
        String argument = arguments[i].ToLower();
        if (argument[0] == '-')
        {
            argument = argument.Substring(1);
            if (argument == "node")
            {
                String nodeName = arguments[i + 1];
                Print("Argument pre load node = " + nodeName);
                LoadNode(nodeName, Vector3(0,0,0));
            }
            else if(argument == "havokfile")
            {
                String havokFile = arguments[i + 1];
                Print("Argument havok file = " + havokFile);
                String nodeFile = HavokConvert(havokFile, false);
                if(!nodeFile.empty)
                {
                    Print("Loading node = " + nodeFile);
                    LoadNode(nodeFile, Vector3(0,0,0));
                }
            }
        }
    }
}


void Start()
{
	OpenConsoleWindow();
    if(!engine.headless)
    {
        SampleStart();
        input.mouseVisible = true;
        

        Text@ nodeText = ui.root.CreateChild("Text", "TEXT_NODE");
        nodeText.position = IntVector2(10,10);
        nodeText.SetFont(cache.GetResource("Font", "Fonts/ConsolaMono.ttf"), 10);
        nodeText.text = "No node";
        nodeText.horizontalAlignment = HA_LEFT;
        nodeText.verticalAlignment = VA_TOP;
        nodeText.color = Color(1.0f,0.0f,0.0f);

        Text@ camreaText = ui.root.CreateChild("Text", "CAMERA_NODE");
        camreaText.SetFont(cache.GetResource("Font", "Fonts/ConsolaMono.ttf"), 10);
        camreaText.horizontalAlignment = HA_RIGHT;
        camreaText.verticalAlignment = VA_TOP;
        camreaText.color = Color(1.0f,0.0f,0.0f);
    }
    
    cache.autoReloadResources = true;
    CreateScene();

    SubscribeToEvents();
    ParseArguments();
}

void Stop()
{
    if(!engine.headless)
        ui.root.RemoveAllChildren();
    previewChildNodes.Clear();
    @cameraNode = null;
    @scene_ = null;
    previewNode.Remove();
    @previewNode = null;
    @camera = null;
}

void SubscribeToEvents()
{
    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("FileChanged", "HandleFileChanged");
    SubscribeToEvent("KeyDown", "MyHandleKeyDown");
    SubscribeToEvent("MayaCommand", "HandleMayaCommand");

    if(engine.headless)
        return;

    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
}

void HandleExit(StringHash eventType, VariantMap& eventData)
{
    engine.Exit();
}

void MyHandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    HandleKeyDown(eventType, eventData);
    int key = eventData["Key"].GetInt();
    if(key == KEY_F3)
    {
        ++drawDebugMode;
        if(drawDebugMode > maxDebugMode)
            drawDebugMode = 0;
    }
    else if(key == KEY_F4)
    {
        ++fillMode;
        if(fillMode > FILL_POINT)
            fillMode = FILL_SOLID;
        camera.fillMode = FillMode(fillMode);
    }
}

String HavokConvert(const String& havokFileName, bool checkTime = true)
{
    String extension = GetExtension(havokFileName).ToLower();
    if(extension != ".hkx" && extension != ".hkt")
    {
        //Print("not a hkx/hkt package file!!!");
        return "";
    }

    String nodeName = GetFileName(havokFileName);
    String nodeFile = "Data/" + havokExportFolder + "/";
    nodeFile += nodeName + "/";
    nodeFile += nodeName + ".xml";

    Print("\n\n============================================\n\n");
    Print("system HavokImporter " + havokFileName);
    Print("node name = " + nodeName);
    Print("node file = " + nodeFile);
    Print("\n\n============================================\n\n");
 
    Array<String> args;
    args.Push(havokFileName);

    int exitCode = fileSystem.SystemRun(fileSystem.programDir + "HavokImporter", args);
    Print("Havok Import result = " + String(exitCode));

    if(exitCode != 0)
        return "";
    
    return nodeFile;
}

void HandleFileChanged(StringHash eventType, VariantMap& eventData)
{
	String resourceName = eventData["ResourceName"].GetString();
    String pathName = eventData["FileName"].GetString();

    String extension = GetExtension(resourceName).ToLower();
    if(extension != ".hkx" && extension != ".hkt")
        return;

    uint curTime = time.systemTime;
    uint dt = curTime - lastTime;
    if(pathName == lastFile && dt < minTime)
    {
        Print("change less than min time, ignore " + pathName);
        return;
    }

    lastTime = curTime;
    lastFile = pathName;

    uint index = pathName.FindLast('/');
    String folder = pathName.Substring(0, index);
    Print(folder);
    if(!folder.EndsWith(havokExportFolder, false))
    {
        Print("not in " + havokExportFolder + " folder.");
        return;
    }

    String nodeFile = HavokConvert(pathName);
    if(nodeFile.empty)
        return;

    Print("Loading node = " + nodeFile);
    LoadNode(nodeFile, Vector3(0,0,0));
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
    MoveCameraFPS(timeStep);

    Text@ uiCamText = ui.root.GetChild("CAMERA_NODE");
    if(uiCamText !is null)
    {
        String cameraPosText = "Camera Position = " + cameraNode.worldPosition.ToString();
        Vector3 eulerAngles = cameraNode.worldRotation.eulerAngles;
        String cameraRotText = "Camera Rotation = " + eulerAngles.ToString();
        cameraText = cameraPosText + "\n" + cameraRotText;
        uiCamText.text = cameraText;
    }
}

void CreateScene()
{
    scene_ = Scene("HKX_PREVIEW_SCENE");
    File loadFile(fileSystem.programDir + sceneToLoad, FILE_READ);
    scene_.LoadXML(loadFile);
    
    cameraNode = scene_.CreateChild("Camera");
    camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 1000.0f;
    camera.fov = 40.824167785f;
    cameraNode.position = Vector3(0.0f, 5.0f, -20.0f);
    cameraNode.LookAt(Vector3(0,0,0));

    CreateGrid();

    if(engine.headless)
        return;

    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
}

void MoveCameraFPS(float timeStep)
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

void DebugDrawNode(DebugRenderer@ debug, Node@ node, float scale, bool depthTest)
{
    debug.AddNode(node, scale, depthTest);
    debug.AddText(node.name, node.worldPosition, Color(0.55,0.55,0.75));

    Array<Component@> comps = node.GetComponents();
    for(uint i=0; i<comps.length; ++i)
    {
        comps[i].DrawDebugGeometry(debug, depthTest);
    }
}

void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    DebugRenderer@ debug = scene_.debugRenderer;
    if (drawDebugMode == 0)
    {
        if(previewNode is null)
            return;
        bool depthTest = false;
        DebugDrawNode(debug, previewNode, 2.0f, depthTest);
        for(uint i=0; i<previewChildNodes.length; ++i)
        {
            DebugDrawNode(debug, previewChildNodes[i], 1.0f, depthTest);
        }
    }
    else if(drawDebugMode == 1)
        renderer.DrawDebugGeometry(false);
    else if(drawDebugMode == 2)
        scene_.physicsWorld.DrawDebugGeometry(debug, false);
}

void LoadNode(const String&in fileName, const Vector3& position)
{
    if (fileName.empty)
        return;

    if (!fileSystem.FileExists(fileName))
    {
        log.Error("No such node file " + fileName);
        MessageBox("No such node file.\n" + fileName);
        return;
    }

    File file(fileName, FILE_READ);
    if (!file.open)
    {
        log.Error("Could not open file " + fileName);
        MessageBox("Could not open file.\n" + fileName);
        return;
    }

    @previewNode = null;
    String extension = GetExtension(fileName);
    if (extension != ".xml")
        previewNode = scene_.Instantiate(file, position, Quaternion(), REPLICATED);
    else
        previewNode = scene_.InstantiateXML(file, position, Quaternion(), REPLICATED);

    nodeStructureText = "";
    GetNodeStructure(nodeStructureText, previewNode, "", true);
    Print(nodeStructureText);
    Text@ text = ui.root.GetChild("TEXT_NODE");
    if(text !is null)
        text.text = nodeStructureText;

    previewChildNodes.Clear();
    previewChildNodes = previewNode.GetChildren(true);
}

Quaternion MayaRotationToUrho(const Vector3&in eulerAngles)
{
    // flip Y and Z axis for right->left handed conversion
    Vector3 flippedRotation(-eulerAngles.x, -eulerAngles.y, -eulerAngles.z);
    // convert XYZ to ZYX
    Quaternion qx(flippedRotation.x, Vector3(1,0,0));
    Quaternion qy(flippedRotation.y, Vector3(0,1,0));
    Quaternion qz(flippedRotation.z, Vector3(0,0,1));
    return qz * qy * qx; // this is the order
}

void HandleMayaCommand(StringHash eventType, VariantMap& eventData)
{
    String cmd = eventData["CommandName"].GetString();
    String data = eventData["CommandData"].GetString();
    if(cmd == "camera_transform")
    {
        Array<String> transform_data = data.Split(',');
        Array<float>  number_data;
        for(uint i=0; i<transform_data.length; ++i)
        {
            number_data.Push(transform_data[i].ToFloat());
        }

        if(number_data.length < 6)
        {
            log.Error("data num not 16!!!");
            return;
        }

        Vector3 t(number_data[0], number_data[1], -number_data[2]);
        Vector3 r(number_data[3], number_data[4], number_data[5]);

        Print("position = " + t.ToString());
        //Print("rotation = " + r.ToString());
        cameraNode.worldPosition = t;
        cameraNode.worldRotation = MayaRotationToUrho(r);
    }
}