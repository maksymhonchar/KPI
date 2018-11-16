using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MonstersHeroesEmulator
{
    // IEnumerable<Tuple<string, int>>
    [Serializable]
    class JacketForAwards : IComparable<JacketForAwards>, IEnumerable<Tuple<string, int>>, ICollectionExtension
    {
        // string: name of award.
        // int: weight of award.
        private List<Tuple<string, int>> Jacket;

        public JacketForAwards()
        {
            Jacket = new List<Tuple<string, int>>();
        }

        public void Add(Tuple<string, int> award)
        {
            this.Jacket.Add(award);
        }

        public int Count
        {
            get
            {
                return this.Jacket.Count;
            }
        }

        public void Clear()
        {
            this.Jacket.Clear();
        }

        public void SuperClear()
        {

        }

        public Tuple<string, int> this[string hexIndex]
        {
            get
            {
                Tuple<string, int> awardToFind = null;
                try
                {
                    awardToFind = this.Jacket.Single(award => award.Item2 == Convert.ToInt32(hexIndex, 16));
                }
                catch (Exception)
                {
                    throw new KeyNotFoundException(String.Format("Invalid weight of award {0}.", Convert.ToInt32(hexIndex, 16)));
                }
                return awardToFind;
            }
            set
            {
                Tuple<string, int> awardToChange = null;
                try
                {
                    awardToChange = this.Jacket.Single(award => award.Item2 == Convert.ToInt32(hexIndex, 16));
                }
                catch (Exception)
                {
                    throw new KeyNotFoundException(String.Format("Invalid weight of award {0}.", Convert.ToInt32(hexIndex, 16)));
                }
                awardToChange = value;
            }
        }

        public int CompareTo(JacketForAwards j)
        {
            if (this.Count > j.Count)
                return 1;
            else if (this.Count < j.Count)
                return -1;
            else
                return 0;
        }

        public IEnumerator<Tuple<string, int>> GetEnumerator()
        {
            return new JacketForAwardsEnumerator(this);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return new JacketForAwardsEnumerator(this);
        }

        public override string ToString()
        {
            return String.Format("Jacket of awards. Count: {0}.", this.Count);
        }
    }
}
