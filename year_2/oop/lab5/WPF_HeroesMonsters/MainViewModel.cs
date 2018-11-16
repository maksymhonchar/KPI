using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;


namespace WPF_HeroesMonsters
{
    public class ViewModelBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
        }

        protected virtual void OnPropertyChanged(PropertyChangedEventArgs args)
        {
            PropertyChanged?.Invoke(this, args);
        }
    }

    /// <summary>
    /// Binding actions to the view with commands.
    /// </summary>
    public class DelegateCommand : ICommand
    {
        public delegate void ICommandOnExecute(object parameter);
        public delegate bool ICommandOnCanExecute(object parameter);

        private ICommandOnExecute _execute;
        private ICommandOnCanExecute _canExecute;

        /// <summary>
        /// The idea of this pattern build an universal command, that takes two delegates: One that is called, when ICommand.Execute(object param) is invoked, and one that evalues the state of the command when ICommand.CanExecute(object param) is called.
        /// </summary>
        public DelegateCommand(ICommandOnExecute onExecuteMethod, ICommandOnCanExecute onCanExecuteMethod)
        {
            _execute = onExecuteMethod;
            _canExecute = onCanExecuteMethod;
        }

        public event EventHandler CanExecuteChanged
        {
            add
            {
                CommandManager.RequerySuggested += value;
            }
            remove
            {
                CommandManager.RequerySuggested -= value;
            }
        }

        public bool CanExecute(object parameter)
        {
            return _canExecute.Invoke(parameter);
        }

        public void Execute(object parameter)
        {
            _execute.Invoke(parameter);
        }
    }

    class MainViewModel : ViewModelBase
    {
        private DelegateCommand exitCommand;

        // A hero model: buffer for heroes.
        public HeroModel HeroArr { get; set; }

        // Fields for creating a new hero.
        public string NameToAdd { get; set; }
        public int DamageToAdd { get; set; }
        public int StrengthToAdd { get; set; }
        public int EvasionToAdd { get; set; }

        // Fields for editing an existing hero.
        public string NameToEdit { get; set; }
        public int DamageToEdit { get; set; }
        public int StrengthToEdit { get; set; }
        public int EvasionToEdit { get; set; }

        public MainViewModel()
        {
            this.HeroArr = HeroModel.Current;
        }

        public ICommand ExitCommand
        {
            get
            {
                if (null == exitCommand)
                    exitCommand = new DelegateCommand(Exit, CanExecuteCommandTrue);
                return exitCommand;
            }
        }

        private void Exit(object parameter)
        {
            // Save data before an exit.
            HeroArr.saveHero();
            Application.Current.Shutdown();
        }

        public bool CanExecuteCommandTrue(object parameter)
        {
            return true;
        }

        private ICommand addHero;
        public ICommand AddHero
        {
            get
            {
                if (null == addHero)
                {
                    addHero = new DelegateCommand(CheckAndInvokeCommand, CanExecuteCommandTrue);
                }
                return addHero;
            }
        }

        public void CheckAndInvokeCommand(object parameter)
        {
            if (NameToAdd == null || NameToAdd.Length < 4)
                throw new ArgumentException("Имя должно быть не меньше четырёх знаков в длину.");
            if (DamageToAdd <= 0 || DamageToAdd >= 500)
                throw new ArgumentException("Урон должен быть больше 0 и не больше 500.");
            if (StrengthToAdd <= 0 || StrengthToAdd >= 500)
            {
                throw new ArgumentException("Сила должна быть больше 0 и не больше 500.");
            }
            if (EvasionToAdd <= 0 || EvasionToAdd > 100)
            {
                throw new ArgumentException("Уклонение должно быть больше 0 и не больше 100.");
            }
            HeroArr.addHero(NameToAdd, DamageToAdd, StrengthToAdd, EvasionToAdd);
        }

        public void deleteHero(object heroObj)
        {
            HeroArr.Remove((Hero)heroObj);
        }

        public void EditHero(object heroObj)
        {
            if (NameToEdit == null || NameToEdit.Length < 4)
                throw new ArgumentException("Имя должно быть не меньше четырёх знаков в длину.");
            if (DamageToEdit <= 0 || DamageToEdit >= 500)
                throw new ArgumentException("Урон должен быть больше 0 и не больше 500.");
            if (StrengthToEdit <= 0 || StrengthToEdit >= 500)
            {
                throw new ArgumentException("Сила должна быть больше 0 и не больше 500.");
            }
            if (EvasionToEdit <= 0 || EvasionToEdit > 100)
            {
                throw new ArgumentException("Уклонение должно быть больше 0 и не больше 100.");
            }

            // Remove the old hero.
            Hero oldHero = (Hero)heroObj;
            int index = HeroArr.getHeroIndex(oldHero);
            HeroArr.removeHero(oldHero);

            // Update the old hero.
            Hero newHero = new Hero();
            newHero.Name = NameToEdit;
            newHero.Damage = DamageToEdit;
            newHero.Strength = StrengthToEdit;
            newHero.Evasion = EvasionToEdit;
            HeroArr.addHero(newHero, index);
        }
    }
}
