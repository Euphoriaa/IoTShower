using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Speech.Recognition;
using System.Speech.Synthesis;
using System.IO.Ports;

namespace VoiceRec
{
    public partial class Form1 : Form
    {
        // defining voice recognition driver and the Serial port for the arduino.
        SpeechRecognitionEngine Engine = new SpeechRecognitionEngine();
        SerialPort mySerial;
        SpeechSynthesizer reader = new SpeechSynthesizer();
        bool Start = false;
        byte tmp = 38;
        byte MaxTmp = 63;
        byte MinTmp = 20;
        byte tmpSerial;
        // build the form, initializing components, serial port, connnection and textBoxes.
        public Form1()
        {
            InitializeComponent();
            mySerial = new SerialPort("COM6", 115200, Parity.None, 8, StopBits.One);
            //Form1_Load();
            mySerial.Open();
            checkBox1.Checked = mySerial.IsOpen;
            ArduinoEcho.Text = "";
            commands.Text = "";
        }

        //starting voice recognition feature.
        public void button1_Click(object sender, EventArgs e)
        {
            Engine.RecognizeAsync(RecognizeMode.Multiple);
            button1.Enabled = false;
        }

        // voice recognition implemention.
        public void Form1_Load(object sender, EventArgs e)
        {
            Choices commands = new Choices();
            commands.Add(new string[] { "Hello Shower", "Warmer", "Colder", "Hot", "Temperate", "Cold" });
            GrammarBuilder gBuilder = new GrammarBuilder();
            gBuilder.Append(commands);
            Grammar grammar = new Grammar(gBuilder);

            Engine.LoadGrammarAsync(grammar);
            Engine.SetInputToDefaultAudioDevice();
            Engine.SpeechRecognized += Engine_SpeechRecognized;
        }

        //set the commands from the voice recognition to the "commands" textbox.

        private void HandleHello()
        {
            if(!Start)
            {
                tmpSerial = 0xFE;
                Start = true;
                WriteTmp();
            }
        }
        private void HandleGoodbye()
        {
            if(Start)
            {
                tmpSerial = 0xFF;
                Start = false;
                WriteTmp();
            }
        }
        public void Engine_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {

            byte newTmp = tmp;
            switch (e.Result.Text)
            {
                case "Hello Shower":
                    HandleHello();
                    commands.Text = e.Result.Text;
                    return;
                case "Goodbye":
                    if (!Start)
                        return;
                    HandleGoodbye();
                    commands.Text = e.Result.Text;
                    return;
                case "Warmer":
                    if (!Start)
                        return;
                    newTmp++;
                    break;
                case "Colder":
                    if (!Start)
                        return;
                    newTmp--;
                    break;
                case "Hot":
                    if (!Start)
                        return;
                    newTmp = 40;
                    break;
                case "Cold":
                    if (!Start)
                        return;
                    newTmp = 20;
                    break;
                case "Temperate":
                    if (!Start)
                        return;
                    newTmp = 30;
                    break;
                default:
                    MessageBox.Show("Something Went wrong");
                    break;
            }
            commands.Text = e.Result.Text;
            if (newTmp > MaxTmp)
            {
                tmp = MaxTmp;
            }
            else if (newTmp < MinTmp)
            {
                tmp = MinTmp;
            }
            else tmp = newTmp;
            tmpSerial = tmp;
            WriteTmp();

        }

        private void WriteTmp()
        {
            char result = Convert.ToChar(tmpSerial);
            mySerial.Write(result.ToString());
        }
        //enabling connection test.
        private void TestConnection_Click(object sender, EventArgs e)
        {
            checkBox1.Checked = mySerial.IsOpen;
            mySerial.Write("A");
            
            string test = mySerial.ReadLine();
            ArduinoEcho.Text += test;
        }

        //send the data in the "commands" textbox to the Arduino.
        private void sendToArduino_Click(object sender, EventArgs e)
        {
            mySerial.WriteLine(commands.Text);
            string test = mySerial.ReadLine();
            commands.Text = "";
            ArduinoEcho.Text = test;

        }

        private void commands_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
