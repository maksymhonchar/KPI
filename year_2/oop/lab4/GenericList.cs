using System;

namespace MonstersHeroesEmulator
{
    /// <summary>
    /// An exception to indicate, that the collection 
    /// doesn't have desired item.
    /// </summary>
    [Serializable]
    public class NoSuchElementException : Exception
    {
        const string errorMsg = "Fatal error: No such element in used collection.";

        public NoSuchElementException() 
        {
            this.LogErrorMessage();
        }

        public NoSuchElementException(string message)
            : base(message)
        {
            this.LogErrorMessage();
            this.HelpLink = "https://vk.com/diferenzial13?w=wall291823738_2514";
            this.Source = "MonstersHeroesEmulator.NoSuchElementException";
        }

        public NoSuchElementException(string message, Exception inner)
            : base(String.Format("{0} - {1}", errorMsg, message), inner)
        {
            this.LogErrorMessage();
        }

        private void LogErrorMessage()
        {
            Logger.LogMessage(errorMsg);
        }
    }

    /// <summary>
    /// Represents a single instance, that holds a value and 
    /// a pointer to next node inside.
    /// </summary>
    [Serializable]
    public class Node<T>
    {
        /// <summary>
        /// Data in current Node.
        /// </summary>
        public T Data { get; set; }

        /// <summary>
        /// Instance of the next Node.
        /// </summary>
        public Node<T> Next { get; set; }

        /// <summary>
        /// A constructor of Node. 
        /// Creates a single node with data and sets a pointer to 
        /// the next Node to null.
        /// </summary>
        /// <param name="data">Data for the Node.</param>
        public Node(T data)
        {
            this.Next = null;
            this.Data = data;
        }
    }

    /// <summary>
    /// A singly linked list which provides all features of CRUD.
    /// <para><see cref="GenericList{T}.Node"/> A node for the GenericList<T>.</para>
    /// </summary>
    [Serializable]
    public class GenericList<T>
    {
        /// <summary>
        /// A head of the list.
        /// This is the place where data is added.
        /// </summary>
        private Node<T> head;

        /// <summary>
        /// Amount of items in the list.
        /// </summary>
        private int size;

        /// <summary>
        /// A constructor for the empty list.
        /// </summary>
        public GenericList()
        {
            this.head = null;
            this.size = 0;
        }

        /// <summary>
        /// Constructor which creates a list with a single item.
        /// </summary>
        /// <param name="data">Data to add to a new list.</param>
        public GenericList(T data)
        {
            this.head = new Node<T>(data);
            this.size = 1;
        }

        /// <summary>
        /// Add an item to beginning of the list.
        /// </summary>
        /// <param name="data">Data to add</param>
        public void addFirst(T data)
        {
            if (data == null)
                throw new NullReferenceException("Input value was null.");

            Node<T> newNode = new Node<T>(data);
            if (size != 0) 
                newNode.Next = head;
            head = newNode;
            size++;       
        }

        /// <summary>
        /// Add an item to end of the list.
        /// </summary>
        /// <param name="data">Data to add.</param>
        public void addLast(T data)
        {
            if (data == null)
                throw new NullReferenceException("Input value was null.");

            Node<T> newNode = new Node<T>(data);
            if (size == 0)
                head = newNode;
            else
            {
                Node<T> tail = head;
                while (tail.Next != null)
                    tail = tail.Next;
                tail.Next = newNode;
            }
            size++;
        }

        /// <summary>
        /// Add an item on specific position in list.
        /// </summary>
        /// <param name="data">Data to add to list.</param>
        /// <param name="index">Index on which to add data.</param>
        public void Add(T data, int index)
        {
            if (data == null)
                throw new NullReferenceException("Cannot add data: input value was null.");
            if (index < 0 || index > size)
                throw new IndexOutOfRangeException(
                    String.Format("Cannot add an element to list: wrong index {0}", index)    
                );

            if (index == 0)
                this.addFirst(data);
            else if (index == (size - 1))
                this.addLast(data);
            else
            {
                Node<T> curNode = head;
                for (int i = 0; i < index - 1; i++)
                {
                    curNode = curNode.Next;
                }
                Node<T> newNode = new Node<T>(data);
                newNode.Next = curNode.Next;
                curNode.Next = newNode;
                size++;
            }
        }

        /// <summary>
        /// Remove data from the beginning of list.
        /// </summary>
        /// <returns>Removed item.</returns>
        public T removeFirst()
        {
            if (size == 0)
                throw new NullReferenceException("Cannot delete an item: there are no items in list.");

            T toDelete = head.Data;
            head = head.Next;
            size--;
            return toDelete;
        }

        /// <summary>
        /// Remove an item on specific position in list.
        /// </summary>
        /// <param name="index">Index on which to delete data.</param>
        /// <returns>Removed item.</returns>
        public T Remove(int index)
        {
            if (index < 0 || index >= size)
                throw new IndexOutOfRangeException(
                    String.Format("Cannot add an element to list: wrong index {0}", index)
                );
            if (size == 0)
                throw new NullReferenceException("Cannot delete an item: there are no items in list.");

            if (index == 0)
                return this.removeFirst();
            Node<T> current = head;
            for (int i = 1; i < index - 1; i++)
                current = current.Next;
            if (index == (size - 1))
            {
                current = current.Next;
            }
            Node<T> deleteNode = current.Next;
            current.Next = deleteNode.Next;
            size--;
            return deleteNode.Data;
        }

        /// <summary>
        /// Remove last element from the list.
        /// </summary>
        /// <returns>Removed item.</returns>
        public T removeLast()
        {
            if (size == 0)
                throw new NullReferenceException("Cannot delete an item: there are no items in list.");

            return this.Remove(this.size - 1);
        }

        /// <summary>
        /// Get an item on specific position in list.
        /// </summary>
        /// <param name="index">Index on which to get data.</param>
        /// <returns>Data on certain index in list.</returns>
        public T Get(int index)
        {
            if (index < 0 || index >= size)
                throw new IndexOutOfRangeException(
                    String.Format("Cannot get an element from list: wrong index {0}", index)
                );

            Node<T> current = head;
            for (int i = 0; i < index - 1; i++)
                current = current.Next;
            return current.Data;
        }

        public T Search(T item)
        {
            if (item == null)
                throw new NullReferenceException("List is not supposed to hold null items.");

            Node<T> current = head;
            for (int i = 0; i < size; i++)
            {
                try
                {
                    if (current.Data.Equals(item))
                        return current.Data;
                }
                catch (Exception)
                {
                    throw;
                }
                current = current.Next;
            }
            throw new NoSuchElementException("Search has not given any results.\n");
        }

        /// <summary>
        /// Print all items in list.
        /// </summary>
        public void Print()
        {
            Node<T> current = head;
            for (int i = 0; i < size; i++)
            {
                try
                {
                    Console.WriteLine(current.Data);
                }
                catch (Exception)
                {
                    throw;
                }
                current = current.Next;
            }
        }

        /// <summary>
        /// Return true, if list is empty.
        /// </summary>
        /// <returns>Status, if list is empty.</returns>
        public bool isEmpty()
        {
            return this.size == 0;
        }

        /// <summary>
        /// Return current amount of items in list.
        /// </summary>
        /// <returns>Amount of items in list.</returns>
        public int getSize()
        {
            return this.size;
        }

    }
}
