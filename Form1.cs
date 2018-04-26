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
namespace VoiceRec
{
    public partial class Form1 : Form
    {
        SpeechRecognitionEngine Engine = new SpeechRecognitionEngine();
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Engine.RecognizeAsync(RecognizeMode.Multiple);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Choices commands = new Choices();
            commands.Add(new string[] { "Hello Shower", "Warmer", "Colder" , "Goodbye"});
            GrammarBuilder gBuilder = new GrammarBuilder();
            gBuilder.Append(commands);
            Grammar grammar = new Grammar(gBuilder);

            Engine.LoadGrammarAsync(grammar);
            Engine.SetInputToDefaultAudioDevice();
            Engine.SpeechRecognized += Engine_SpeechRecognized;
        }

        private void Engine_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            switch(e.Result.Text)
            {
                case "Hello Shower":
                    MessageBox.Show("Hello User");
                    break;
                case "Warmer":
                    MessageBox.Show("Warmer");
                    break;
                case "Colder":
                    MessageBox.Show("Colder");
                    break;
                case "Goodbye":
                    MessageBox.Show("Bye");
                    break;
                default:
                    MessageBox.Show("Something Went wrong");
                    break;
            }
        }
    }
}
