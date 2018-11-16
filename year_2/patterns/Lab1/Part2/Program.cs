using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1_2
{
    class Program
    {
        static void Main(string[] args)
        {
            SchoolWithDepartments school = new SchoolWithDepartments();

            // Add departments to the school.
            school.AddDepartment(new Department("Dep1", 10000, 2000));
            school.AddDepartment(new Department("Dep2", 10000, 3000));

            // Add workers to departments.
            int idCounter = 0;
            foreach (var department in school.departments)
            {
                department.AddComponent(new Worker(idCounter++));
                department.AddComponent(new Worker(idCounter++));
            }

            // Pay salary to each worker.
            foreach (var department in school.departments)
            {
                department.PaySalary(department.salary);
            }

            // Print bank accounts of workers.
            foreach (var department in school.departments)
            {
                Console.WriteLine("Dep {0}", department.Name);
                department.PrintAccountStats();
                foreach (var worker in department.WorkerNodes)
                {
                    worker.PrintAccountStats();
                }
            }

            Console.ReadKey();
        }
    }

    interface IMoneyNode
    {
        /// <summary>
        /// Paying salary to each subunit.
        /// </summary>
        /// <param name="toPay"></param>
        void PaySalary(int toPay);

        /// <summary>
        /// Adding a subunit to current node.
        /// </summary>
        /// <param name="moneyNode"></param>
        void AddComponent(IMoneyNode moneyNode);

        /// <summary>
        /// Print account stats of a current MoneyNode.
        /// </summary>
        void PrintAccountStats();
    }

    class SchoolWithDepartments
    {
        public List<Department> departments { get; private set; }

        public SchoolWithDepartments()
        {
            this.departments = new List<Department>();
        }
        
        public void AddDepartment(Department depToAdd)
        {
            this.departments.Add(depToAdd);
        }
    }

    class Department : IMoneyNode
    {
        /// <summary>
        /// Name of department.
        /// </summary>
        public string Name { get; private set; }

        /// <summary>
        /// List of workers in a department.
        /// </summary>
        public List<IMoneyNode> WorkerNodes { get; private set; }

        /// <summary>
        /// Total money from above to pay to workers.
        /// </summary>
        private int money;

        /// <summary>
        /// Salary to pay to each worker.
        /// </summary>
        public int salary;

        public Department(string name, int money, int salary)
        {
            this.Name = name;
            this.WorkerNodes = new List<IMoneyNode>();
            this.money = money;
            this.salary = salary;
        }

        /// <summary>
        /// Pay salary to each worker in department.
        /// </summary>
        /// <param name="toPay">How much to pay to each worker.</param>
        public void PaySalary(int toPay)
        {
            foreach (var moneyNode in WorkerNodes)
            {
                if (this.money >= toPay)
                {
                    this.money -= toPay;
                    moneyNode.PaySalary(toPay);
                }
                else
                {
                    Console.WriteLine("No money left in department {0}.", this.Name);
                }
            }
        }

        /// <summary>
        /// Add a worker to department.
        /// </summary>
        /// <param name="workerNode">A worker node to add.</param>
        public void AddComponent(IMoneyNode workerNode)
        {
            this.WorkerNodes.Add(workerNode);
        }

        public void PrintAccountStats()
        {
            Console.WriteLine("Department {0} has {1} in his account.", this.Name, this.money);
        }
    }

    class Worker : IMoneyNode
    {
        public int WorkerIdToPay { get; set; }
        public int BankAccount { get; private set; }

        public Worker(int workerIdToPay)
        {
            this.WorkerIdToPay = workerIdToPay;
        }

        public void PaySalary(int toPay)
        {
            if (toPay > 0)
            {
                this.BankAccount += toPay;
                Console.WriteLine("A worker id{0} received his salary {1}USD", this.WorkerIdToPay, toPay);
            }
        }

        public void AddComponent(IMoneyNode moneyNode)
        {
            Console.WriteLine("Cannot add a component to worker.");
        }

        public void PrintAccountStats()
        {
            Console.WriteLine("A worker id{0} has {1} USD in his bank account.", this.WorkerIdToPay, this.BankAccount);
        }
    }
}
