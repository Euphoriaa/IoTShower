using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using VoiceRec;
using System.Speech.Recognition;

namespace MainShower
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        SpeechRecognitionEngine Engine = new SpeechRecognitionEngine();

        public MainWindow()
        {
            InitializeComponent();
            voiceRecogniseLogic();
        }

        private void startVoiceRecognise_Click(object sender, RoutedEventArgs e)
        {
            Engine.RecognizeAsync(RecognizeMode.Multiple);
        }

        private void voiceRecogniseLogic()
        {
            Choices commands = new Choices();
            commands.Add(new string[] { "Hello Shower", "Warmer", "Colder", "Goodbye" });
            GrammarBuilder gBuilder = new GrammarBuilder();
            gBuilder.Append(commands);
            Grammar grammar = new Grammar(gBuilder);

            Engine.LoadGrammarAsync(grammar);
            Engine.SetInputToDefaultAudioDevice();
            Engine.SpeechRecognized += Engine_SpeechRecognized;

        }

        public void Engine_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            switch (e.Result.Text)
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
