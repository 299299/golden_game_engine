using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ToolCenter
{
    public partial class HashForm : Form
    {
        Dictionary<uint, string> m_stringTable;

        public HashForm()
        {
            InitializeComponent();
            m_stringTable = new Dictionary<uint, string>();
            loadStringTable("string_table.txt");
        }

        private void buttonShow_Click(object sender, EventArgs e)
        {
            string str = textBox_String.Text;
            if (str.Length != 0)
            {
                uint hashValue = CaculateHash(str);
                label_result.Text = "x= " + hashValue.ToString("x") + " d= " + hashValue.ToString();
            }

            str = textBox_hash.Text;
            if (str.Length != 0)
            {
                uint key = uint.Parse(str);
                string value;
                if (m_stringTable.TryGetValue(key, out value))
                    lable_result2.Text = value;
                else
                    lable_result2.Text = "not found :(  is it in string_table.txt ?";
            }
        }

        private uint SDBMHash(uint hash, char c)
        {
            return c + (hash << 6) + (hash << 16) - hash;
        }

        private uint CaculateHash(string str)
        {
            uint hash = 0;
            if (str.Length == 0)
                return hash;
            string lowerStr = str.ToLower();
            for (int i = 0; i < lowerStr.Length; ++i)
            {
                hash = SDBMHash(hash, lowerStr[i]);
            }
            return hash;
        }

        private void loadStringTable(string str)
        {
            System.IO.StreamReader file = new System.IO.StreamReader(str);
            string line;
            while ((line = file.ReadLine()) != null)
            {
                string[] strs = line.Split(',');
                uint key = uint.Parse(strs[0]);
                string value = strs[2];
                m_stringTable[key] = value;
            }
            file.Close();
        }
    }
}
