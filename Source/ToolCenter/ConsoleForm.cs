using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;
using WebSocketSharp;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace ToolCenter
{
    public partial class ConsoleForm : Form
    {
        WebSocket m_ws;
        System.IO.FileSystemWatcher m_resourceWatcher;
        string m_lastFile;
        DateTime m_lastTime;

        public ConsoleForm()
        {
            InitializeComponent();
            m_resourceWatcher = new FileSystemWatcher();
            m_resourceWatcher.Path = Utils.getIntermediateDir();
            m_resourceWatcher.IncludeSubdirectories = true;
            m_resourceWatcher.NotifyFilter = NotifyFilters.LastAccess |
                                             NotifyFilters.LastWrite | 
                                             NotifyFilters.Size |
                                             NotifyFilters.FileName;
            m_resourceWatcher.Filter = "*.*";
            m_resourceWatcher.Changed += new FileSystemEventHandler(OnFileChanged);
            m_resourceWatcher.Created += new FileSystemEventHandler(OnFileChanged);
            m_resourceWatcher.Deleted += new FileSystemEventHandler(OnFileChanged);
            m_resourceWatcher.Renamed += new RenamedEventHandler(OnNameChanged);
            comboBox_type.SelectedIndex = 0;
        }

        private bool FilterFileName(string fileName)
        {
            string[] filters = {"tmp", "db"};
            foreach(string filter in filters)
            {
                if(fileName.ToLower().EndsWith(filter))
                    return true;
            }
            return false;
        }

        private void OnFileChanged(object sender, FileSystemEventArgs e)
        {
            if (Path.GetExtension(e.Name) == string.Empty)
                return;
            if (FilterFileName(e.Name))
                return;
            string logMsg = "FileChanged ";
            logMsg += e.ChangeType.ToString();
            logMsg += " FileName = ";
            logMsg += e.Name;
            PrintLog(logMsg, Color.DarkOrange);
            if (e.ChangeType == WatcherChangeTypes.Deleted)
                return;
            resource_hot_load(e.Name);
        }

        private void OnNameChanged(object sender, RenamedEventArgs e)
        {
            string logMsg = "ReName form ";
            logMsg += e.OldName;
            logMsg += " ---> ";
            logMsg += e.Name;
            PrintLog(logMsg, Color.DarkCyan);
            if (FilterFileName(e.Name))
                return;
            if (Path.GetExtension(e.Name) == string.Empty)
                return;
            resource_hot_load(e.Name);
        }

        private void OnWebSocketOpen(object sender, EventArgs e)
        {
            PrintLog("WebSocket Opend", Color.Blue);
        }

        private void OnWebSocketClose(object sender, CloseEventArgs e)
        {
            if (e.Code == 1006)
                return;
            PrintLog("WebSocket Closed", Color.Red);
        }

        private void OnWebSocketError(object sender, WebSocketSharp.ErrorEventArgs e)
        {
            Console.WriteLine(e.Message);
            PrintLog(e.Message, Color.Red);
        }

        private void OnWebSocketMessage(object sender, MessageEventArgs e)
        {
            //if (m_closed) return;
            if (e.Type != Opcode.Binary) return;
            char[] chars = System.Text.Encoding.UTF8.GetString(e.RawData).ToCharArray();
            List<String> strList = buffer_to_string(chars);
            foreach(string str in strList)
            {
                JObject jsonObject = null;
                //if (str[str.Length - 1] != '}')
                //    str.Remove(str.Length - 1, 1);
                try
                {
                    jsonObject = JObject.Parse(str);
                }
                catch (Newtonsoft.Json.JsonReaderException ex)
                {
                    PrintLog(ex.Message, Color.Red);
                    continue;
                }
                
                string typeName = (string)(jsonObject["type"]);
                if (typeName == "logging.msg")
                {
                    string msg = (string)(jsonObject["msg"]);
                    string engineHead = "[ENGINE LOG] ";
                    int level = (int)(jsonObject["lvl"]);
                    Color[] logColors = {Color.Black, Color.Blue, Color.DarkBlue, Color.Red, Color.Purple};
                    PrintLog(engineHead + msg, logColors[level]);
                }
            }
        }

        private void send_string(string str)
        {
            if (m_ws == null)
                return;
            if (m_ws.ReadyState != WebSocketState.Open)
                return;
            PrintLog("send remote -> " + str, Color.DodgerBlue);
            byte[] bytes = string_to_buffer(str);
            //PrintLog("Send Byte len:" + bytes.Length.ToString(), Color.Red);
            m_ws.Send(bytes);
        }

        private string json_string(string key, string value)
        {
            return string.Format("\"{0}\":\"{1}\"", key, value);
        }

        private void send_remote_cmd(string cmd, string data1, string data2)
        {
            string strCmd = json_string("command", cmd);
            string strData1 = json_string("data1", data1);
            string strData2 = json_string("data2", data2);
            string strDesc = json_string("type", "remote.command");
            string str = "{";
            str += strCmd;
            str += ",";
            str += strData1;
            str += ",";
            str += strData2;
            str += ",";
            str += strDesc;
            str += "}";
            send_string(str);
        }

        private byte[] string_to_buffer(string str)
        {
            int strLen = str.Length;
            byte[] retArray = new byte[strLen+2];
            retArray[0] = (byte)(strLen % 256);
            retArray[1] = (byte)(strLen / 256);
            int index = 2;
            foreach (char c in str)
            {
                retArray[index++] = (byte)(c);
            }
            return retArray;
        }

        private List<string> buffer_to_string(char[] buffer)
        {
            int bufferlen = buffer.Length;
            int offset = 0;
            List<string> stringList = new List<string>();
            while (offset < bufferlen)
            {
                byte b0 = (byte)buffer[offset];
                byte b1 = (byte)buffer[offset + 1];
                int arg0 = (int)(b0);
                int arg1 = (int)(b1) * 256;
                int texLen = arg0 + arg1;
                int texStart = offset + 2;
                int texLeft = bufferlen - offset - 2;
                if (texLen > texLeft)
                {
                    texLen = texLeft;
                }
                string str = new string(buffer, texStart, texLen);
                stringList.Add(str);
                offset = texStart + texLen;
            }
            return stringList;
        }

        public void PrintLog(string msg, Color color)
        {
            LogTextEvent(richTextBox_log, color, msg);
        }

        public void LogTextEvent(RichTextBox TextEventLog, Color TextColor, string EventText)
        {
            if (TextEventLog.InvokeRequired)
            {
                TextEventLog.BeginInvoke(new Action(delegate
                {
                    LogTextEvent(TextEventLog, TextColor, EventText);
                }));
                return;
            }

            string nDateTime = DateTime.Now.ToString("hh:mm:ss tt") + " - ";

            // color text.
            TextEventLog.SelectionStart = TextEventLog.Text.Length;
            TextEventLog.SelectionColor = TextColor;

            // newline if first line, append if else.
            if (TextEventLog.Lines.Length == 0)
            {
                TextEventLog.AppendText(nDateTime + EventText);
                TextEventLog.ScrollToCaret();
                TextEventLog.AppendText(System.Environment.NewLine);
            }
            else
            {
                TextEventLog.AppendText(nDateTime + EventText + System.Environment.NewLine);
                TextEventLog.ScrollToCaret();
            }
        }

        private void ConsoleForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (m_ws == null)
                return;
            m_ws.Close();
        }

        private void checkBox_watch_CheckedChanged(object sender, EventArgs e)
        {
            m_resourceWatcher.EnableRaisingEvents = checkBox_watch.Enabled;
        }

        private void resource_hot_load(string fileName)
        {
            PrintLog("resource hot load " + fileName, Color.DarkRed);
            DateTime now = DateTime.Now;
            TimeSpan diff = now - m_lastTime;
            m_lastTime = now;
            if (diff.TotalSeconds < 2 && m_lastFile == fileName)
                return;
            m_lastFile = fileName;
            string filePath = "intermediate/";
            filePath += fileName;
            string outputPath = "data/" + Path.GetDirectoryName(fileName);
            string args = "-f ";
            args += filePath;
            args += " -o ";
            args += outputPath;
            Utils.Run(Utils.getApplicationDir(), "DataCompiler.exe", args);

            System.IO.StreamReader file;
            try
            {
                file = new System.IO.StreamReader("data_compiler_result.txt");
            }
            catch (System.IO.FileNotFoundException e)
            {
                Console.WriteLine(e.Message);
                return;
            }
            string line;
            while ((line = file.ReadLine()) != null)
            {
                send_remote_cmd("reload_resource_file", line, "");
            }
            file.Close();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            if (textBox_Host.Text.Length == 0)
                return;
            string url = "ws://" + textBox_Host.Text;
            m_ws = new WebSocket(url);
            m_ws.OnOpen += new EventHandler(OnWebSocketOpen);
            m_ws.OnClose += new EventHandler<CloseEventArgs>(OnWebSocketClose);
            m_ws.OnError += new EventHandler<WebSocketSharp.ErrorEventArgs>(OnWebSocketError);
            m_ws.OnMessage += new EventHandler<MessageEventArgs>(OnWebSocketMessage);
            m_ws.Log.Level = LogLevel.Debug;
            m_ws.ConnectAsync();
        }

        private void textBox_input_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != (char)Keys.Return)
                return;
            if (textBox_input.Text.Length == 0)
                return;
            int sendType = comboBox_type.SelectedIndex;
            if (sendType == 0)
            {
                string[] args = textBox_input.Text.Split(' ');
                if (args.Length > 2)
                {
                    send_remote_cmd(args[0], args[1], args[2]);
                }
                else if (args.Length > 1)
                {
                    send_remote_cmd(args[0], args[1], "");
                }
                else
                {
                    send_remote_cmd(args[0], "", "");
                }
            }
            else if (sendType == 1)
            {

            }
            textBox_input.Text = "";
        }
    }

    
}
