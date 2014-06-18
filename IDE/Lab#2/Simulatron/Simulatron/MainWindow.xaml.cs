//default
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


//user defined
using System.Speech.Synthesis; //userd for speech
using System.Windows.Media.Animation;
using System.Media;
using System.Windows.Controls.Primitives;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Diagnostics;

namespace Simulatron
{
    public partial class MainWindow : Window
    {
        //button checkers
        bool bSmall1 = false;
        bool once1 = true;
        bool bSmall2 = false;
        bool bSmall4 = false;
        bool popupShow = true;
        
        //speech synthetization
        SpeechSynthesizer synthesizer = new SpeechSynthesizer();
        
        //sounds player
        MediaPlayer mediaPlayer = new MediaPlayer();

        public MainWindow()
        {
            InitializeComponent();
            synthesizer.Volume = 100;  // 0...100
            synthesizer.Rate   = 0;     // -10...10
            synthesizer.SpeakAsync("Welcome to Simulatron!");
        }

        private void buttonSmall1(object sender, RoutedEventArgs e)
        {
            synthesizer.SpeakAsync(bSmall1 ? "We started the flight " : "You found run button.");
            
            
            if (once1 && bSmall1)
            {
                once1 = false;
                String pathToAudio = "Sounds/start.mp3";
                mediaPlayer.Open(new Uri(pathToAudio, UriKind.Relative));
                mediaPlayer.Play();
                var a = new DoubleAnimation
                {
                    From = 0.0,
                    To = 1.0,
                    FillBehavior = FillBehavior.Stop,
                    BeginTime = TimeSpan.FromSeconds(0),
                    Duration = new Duration(TimeSpan.FromSeconds(5))
                };
                var storyboard = new Storyboard();
                bgBlueAppear.Visibility = System.Windows.Visibility.Visible;
                storyboard.Children.Add(a);
                Storyboard.SetTarget(a, bgBlueAppear);
                Storyboard.SetTargetProperty(a, new PropertyPath(OpacityProperty));
                //storyboard.Completed += delegate { bgBlueAppear.Visibility = System.Windows.Visibility.Hidden; };
                storyboard.Begin();
                //Assert.AreEqual(once1, true);
                //Assert.AreEqual(bSmall1, true);
            }
       
            bSmall1 = true;
        }

        private void buttonSmall2(object sender, RoutedEventArgs e)
        {
            if (bSmall1)
            {
                synthesizer.SpeakAsync(bSmall2 ? "Fyeah" : "O, You found the fire button.");
                if (bSmall2)
                {
                    once1 = false;
                    String pathToAudio = "Sounds/fire.mp3";
                    mediaPlayer.Open(new Uri(pathToAudio, UriKind.Relative));
                    mediaPlayer.Play();
                    
                    var a = new DoubleAnimation
                    {
                        From = 0.0,
                        To = 1.0,
                        FillBehavior = FillBehavior.Stop,
                        BeginTime = TimeSpan.FromSeconds(0),
                        Duration = new Duration(TimeSpan.FromSeconds(5))
                    };

                    var storyboard = new Storyboard();
                    bgBlueFire.Visibility = System.Windows.Visibility.Visible;
                    storyboard.Children.Add(a);
                    Storyboard.SetTarget(a, bgBlueFire);
                    Storyboard.SetTargetProperty(a, new PropertyPath(OpacityProperty));
                    storyboard.Completed += delegate { bgBlueFire.Visibility = System.Windows.Visibility.Hidden; };
                    storyboard.Begin();
                }
                bSmall2 = true;
            }//endif
        }//endbsmall2

        private void buttonSmall3(object sender, RoutedEventArgs e)
        {
            if (bSmall1 && popupShow)
            {
                about.IsOpen = true;
            }
            else
            {
                about.IsOpen = false;
            }
            popupShow = !popupShow;
        }

        private void buttonSmall4(object sender, RoutedEventArgs e)
        {
            if (bSmall1)
            {
                synthesizer.SpeakAsync("It was a trap. You are dead. Good bye Aliens!");
                if (bSmall4)
                {
                    endofstory.Visibility = System.Windows.Visibility.Visible;
                    Stopwatch sw = new Stopwatch();
                    sw.Start();
                    if (sw.Elapsed > TimeSpan.FromMilliseconds(200)) return;      
                }
                    bSmall4 = true;
                
            }
        }

    }
}
