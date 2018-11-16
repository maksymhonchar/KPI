using System;

namespace OOP_Lab1_Gonchar_Maxim_KP51
{
    /// <summary>
    /// <para>Class, that represents a Model.</para>
    /// <para>Model can be either Hero, or a Monster.</para>
    /// <para>Has such virtual methods:</para>
    /// </summary>
    public class Model
    {
        /// <summary>
        /// <para>ID for the Model instance. This field is unique for each Model instance.</para>
        /// <para>Set Method is just to check value of current ID counter.</para>
        /// </summary>
        public static int Id { get; set; }

        /// <summary>
        /// <para>Default Model name.</para>
        /// </summary>
        protected string Name { get; set; }

        /// <summary>
        /// <para>Amount of Models health.</para>
        /// </summary>
        private int health;
        protected int Health
        {
            get
            {
                return this.health;
            }

            set
            {
                this.health = (health > 100) ? 100 : value;
            }
        }

        /// <summary>
        /// <para>Amount of Models damage.</para>
        /// </summary>
        protected int Damage { get; set; }

        /// <summary>
        /// <para>Current coordinates on the map by OX or OY axis.</para>
        /// <para>Is implemented as class property.</para>
        /// <see cref="PosX"/>
        /// <see cref="PosY"/>
        /// </summary>
        private double posY, posX;

        /// <summary>
        /// <para>Get is default.</para>
        /// <para>Set is manual - if there is a free place on the map, fill the posX with value.</para>
        /// <para>Otherwise fill it with 0.</para>
        /// <see cref="posX"/>
        /// </summary>
        protected double PosX
        {
            get
            {
                return posX;
            }

            set
            {
                posX = (GameUtils.checkIfPositionIsFree(posX: posX)) ? value : 0;
            }
        }

        /// <summary>
        /// <para>Get is default.</para>
        /// <para>Set is manual - if there is a free place on the map, fill the posY with value.</para>
        /// <para>Otherwise fill it with 0.</para>
        /// <see cref="posY"/>
        /// </summary>
        protected double PosY
        {
            get
            {
                return posY;
            }

            set
            {
                posY = (GameUtils.checkIfPositionIsFree(posY: posY)) ? value : 0;
            }
        }

        /// <summary>
        /// <para>Default constructor, which fills health and name with default values.</para>
        /// </summary>
        public Model()
        {
            this.Health = 100;
            this.Name = "model-" + (++Id).ToString();
            Logger.printMsgSystem(String.Format("Model {0} has been created.", this.Name));
        }

        /// <summary>
        /// <para>Constructor, which sets specific amount of health and sets a position to the Model instance.</para>
        /// </summary>
        /// <param name="health">Health amount</param>
        /// <param name="posX">Position by OX axis.</param>
        /// <param name="posY">Position by OY axis.</param>
        public Model(int health, double posX, double posY)
            : this()
        {
            this.Health = health;
            this.PosX = posX;
            this.PosY = posY;
            Logger.printMsgSystem(String.Format("Model {0} has been created. It is on {1}-{2} now.", this.Name, this.PosX, this.PosY));
        }

        /// <summary>
        /// <para>Get current position on the map by specific formula.</para>
        /// </summary>
        /// <returns>Current position on the map.</returns>
        public double getSpecificPosition()
        {
            return Math.Sqrt(Math.Pow(PosX, 2) + Math.Pow(PosY, 2));
        }

        /// <summary>
        /// <para>Set a specific position to X and Y coordinates simultaneously</para>
        /// </summary>
        /// <param name="posX">OX axis coordinates.</param>
        /// <param name="posY">OY axis coordinates.</param>
        public void setSpecificPosition(double posX, double posY)
        {
            this.PosX = posX;
            this.PosY = posY;
        }

        public override string ToString()
        {
            return String.Format(
                "Model:{0}. Coord:({1}:{2}). Health:{3}.",
                this.Name,
                this.PosX, this.PosY,
                this.Health
                );
        }
    }
}
