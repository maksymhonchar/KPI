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
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;


namespace WPF_HeroesMonsters
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private MainViewModel DataContext;

        public MainWindow()
        {
            InitializeComponent();

            DataContext = new MainViewModel();

            //// Deserialization.
            //FileStream fs = new FileStream("swordsman.dat", FileMode.Open);
            //BinaryFormatter bf = new BinaryFormatter();
            //Hero[] __heroBuf = (Hero[])bf.Deserialize(fs);
            //fs.Close();

            NameField.TextChanged += TextBoxOnChange;
            DamageField.TextChanged += TextBoxOnChange;
            StrengthField.TextChanged += TextBoxOnChange;
            EvasionField.TextChanged += TextBoxOnChange;
        }

        private void TextBoxOnChange(object sender, EventArgs eventArgs)
        {
            bool nameFieldInValid = NameField.Text.Length <= 4;
            bool dmgFieldInValid = DamageField.Text.Length == 0;
            bool strengthFieldInValid = StrengthField.Text.Length == 0;
            bool evasionFieldInValid = EvasionField.Text.Length == 0;
 
            // Check if input in creating a hero is correct.
            if (nameFieldInValid || dmgFieldInValid || strengthFieldInValid || evasionFieldInValid)
            {
                btnAddHero.IsEnabled = false;
            }
            else
            {
                // Try to avoid incorrect format, by getting Int32 value from textfields.
                try
                {
                    // Check range of the numbers.
                    int dmg = Int32.Parse(DamageField.Text);
                    int strngh = Int32.Parse(StrengthField.Text);
                    int evasn = Int32.Parse(EvasionField.Text);
                    if (dmg < 0 || strngh < 0 || evasn < 0 || 
                        dmg >= 500 || strngh >= 500 || evasn >= 100)
                    {
                        btnAddHero.IsEnabled = false;
                    }
                    else
                    {
                        btnAddHero.IsEnabled = true;
                    }
                }
                catch (Exception exception)
                {
                    if (exception is FormatException || exception is OverflowException)
                    {
                        btnAddHero.IsEnabled = false;
                    }
                }
            }
        }

        public void MW_deleteHero(object sender, RoutedEventArgs e)
        {
            DataContext.deleteHero((Hero)HeroesList.SelectedItem);
        }

        public void MW_editHero(object sender, RoutedEventArgs e)
        {
            bool nameFieldInValid = NameEditField.Text.Length <= 4;
            bool dmgFieldInValid = DmgEditField.Text.Length == 0;
            bool strengthFieldInValid = StrengthEditField.Text.Length == 0;
            bool evasionFieldInValid = EvasionField.Text.Length == 0;

            // Check if input in creating a hero is correct.
            if (nameFieldInValid || dmgFieldInValid || strengthFieldInValid || evasionFieldInValid)
            {
                btnAddHero.IsEnabled = false;
            }
            else
            {
                // Try to avoid incorrect format, by getting Int32 value from textfields.
                try
                {
                    // Check range of the numbers.
                    int dmg = Int32.Parse(DmgEditField.Text);
                    int strngh = Int32.Parse(StrengthEditField.Text);
                    int evasn = Int32.Parse(EvasionField.Text);
                    if (dmg < 0 || strngh < 0 || evasn < 0 ||
                        dmg >= 500 || strngh >= 500 || evasn >= 100)
                    {
                        btnAddHero.IsEnabled = false;
                    }
                    else
                    {
                        btnAddHero.IsEnabled = true;
                    }
                }
                catch (Exception exception)
                {
                    if (exception is FormatException || exception is OverflowException)
                    {
                        btnAddHero.IsEnabled = false;
                    }
                }
            }

            // Update fields.
            DataContext.NameToEdit = NameEditField.Text;
            DataContext.DamageToEdit = Int32.Parse(DmgEditField.Text);
            DataContext.StrengthToEdit = Int32.Parse(StrengthEditField.Text);
            DataContext.EvasionToEdit = Int32.Parse(EvasionEditField.Text);

            // Call function foro editing.
            DataContext.EditHero((Hero)HeroesList.SelectedItem);
        }
    }
}
