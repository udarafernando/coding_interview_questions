// ****************
// 2.4 Partition
// ****************

template <typename T>
struct Node
{
    Node(const T& a_data, Node<T>* a_next = nullptr) { m_data = a_data; m_next = a_next; }
    static Node<T> *listFromVector(const std::vector<T>& a_v)
    {
        Node<T> *head = nullptr;
        
        for (auto it = a_v.rbegin(); it != a_v.rend(); ++it)
        {
            head = new Node(*it, head);
        }
        
        return head;
    }
    
    void print() 
    {
        Node<T> *curr = this;
        while (curr)
        {
            std::cout << curr->m_data << " ";
            curr = curr->m_next;
        }
        std::cout << std::endl;
    }
    
    static Node<T> *partition(Node<T> *n, const T pivot)
    {
        if (!n) return nullptr; 
        
        // There is now at least one element
        Node<T> *head = n;
        Node<T> *tail = n;
        
        // Need to do this, so we don't return a circular list in the case of a single-element list
        n = n->m_next;
        while (n)
        {
            Node<T> *next = n->m_next;
            if (n->m_data < pivot) 
            {
                n->m_next = head;
                head = n;
            }
            else
            {
                n->m_next = nullptr;
                tail->m_next = n;
                tail = n;
            }
            n = next;
        }
        
        return head;
    }
    
    T m_data;
    Node<T>* m_next;
};


void problem2_4()
{
    Node<int> *list = Node<int>::listFromVector({3,5,8,5,10,2,1});
    list->print();
    list = Node<int>::partition(list, 5);
    list->print();
}