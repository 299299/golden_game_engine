

String lastConsoleCommand;

float timeScale = 1.0f;
Array<float> timeScales = { 0.1f, 0.25f, 0.5f, 0.75f, 1.0f, 2.5f, 5.0f, 10.0f};
uint currentTimeScaleIndex = 0;

//------------------------------------------------------------------------------------------
//-------- SCENE Functions -----------------------------------------------------------------
//------------------------------------------------------------------------------------------
void SwitchTimeScale()
{
	timeScale = timeScales[currentTimeScaleIndex];
    ++currentTimeScaleIndex;
    if(currentTimeScaleIndex >= timeScales.length)
        currentTimeScaleIndex = 0;
    script.defaultScene.timeScale = timeScale;
}


//----------------------------------------------------------------------------------------
//-------- GUI Functions -----------------------------------------------------------------
//----------------------------------------------------------------------------------------
void CreateAnimationControlWindow()
{
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

//----------------------------------------------------------------------------------------
//-------- Console Input Functions For my linux test machine -----------------------------
//----------------------------------------------------------------------------------------
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

//--------------------------------------------------------------
//-------- Animation DUMP Functions-----------------------------
//--------------------------------------------------------------
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

//---------------------------------------------------------------
//-------- Animation DEBUG Functions-----------------------------
//---------------------------------------------------------------
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

void StepFrame(int dFrame)
{
    int iFrame = animController.GetReplayFrame();
    iFrame += dFrame;
    int totalFrames = animController.GetRecordedFrames();
    if(iFrame < 0)
        iFrame += totalFrames;
    if(iFrame >= totalFrames)
        iFrame -= totalFrames;
    animController.SetReplayFrame(iFrame);

    Slider@ slider = ui.root.GetChild("REPLAY_SLIDER", true);
    Text@ text = ui.root.GetChild("REPLAY_TEXT", true);
    slider.value = iFrame;
    text.text = "Replay Frame = " + String(iFrame);  
}