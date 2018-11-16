namespace MonstersHeroesEmulator
{
    interface IGameItem
    {
        string Name { get; set; }

        int calculateEfficiency();

        void increaseDurability(int value);
        void decreaseDurability(int value);
    }
}
