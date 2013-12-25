
String sceneToLoad = "Data/Scenes/testScene.xml";
Scene@ scene_;
Node@ characterNode;
AnimatorController@ animController;


void Start()
{
    // Enable automatic resource reloading
    cache.autoReloadResources = true;
    CreateScene();
    SubscribeToEvents();
}

void Stop()
{
    
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
    animController = characterNode.GetComponent("AnimatorController");
    animController.Start();
}


void SubscribeToEvents()
{
    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent(scene_, "ScenePostUpdate", "HandleScenePostUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
}

void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
}


