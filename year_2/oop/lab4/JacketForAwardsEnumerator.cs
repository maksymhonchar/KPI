using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MonstersHeroesEmulator
{
    // IEnumerator <-> IEnumerable
    // IDisposable is included in IEnumerator
    [Serializable]
    class JacketForAwardsEnumerator : IEnumerator<Tuple<string, int>>
    {
        private JacketForAwards jacket;
        private int index;
        private Tuple<string, int> current;
        private int __prevIndex;

        public JacketForAwardsEnumerator(JacketForAwards jacket)
        {
            this.jacket = jacket;
            this.index = -1;
            this.current = default(Tuple<string, int>);
            this.__prevIndex = 0;
        }


        public Tuple<string, int> Current
        {
            get
            {
                return this.current;
            }
        }

        object IEnumerator.Current
        {
            get
            {
                return this.current;
            }
        }

        public void Dispose()
        {
            this.jacket = null;
            this.index = -1;
            this.current = default(Tuple<string, int>);
            this.__prevIndex = 0;
        }

        public bool MoveNext()
        {
            this.index++;

            if (this.index >= this.jacket.Count)
            {
                return false;
            }
            else
            {
                int __index = __prevIndex;
                bool __flg = false;
                Tuple<string, int> __current = null;

                // go through first 100 elements: from 0 to 100 and find the first one.
                while (!__flg && __index <= 100)
                {
                    /* For testing purposes only. */
                    // Console.WriteLine("0x" + __index.ToString("X"));
                    try
                    {
                        __current = this.jacket["0x" + __index++.ToString("X")];
                    }
                    catch (Exception)
                    {
                        continue;
                    }
                    __flg = true;
                    __prevIndex = __index;
                }

                this.current = __current;
            }
            return true;
        }

        public void Reset()
        {
            this.current = default(Tuple<string, int>);
            this.index = -1;
            this.__prevIndex = 0;
        }
    }
}
