#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* mergeTwoLists(ListNode* one, ListNode* two)
{
    if (one == NULL)
    {
        return two;
    }
    if (two == NULL)
    {
        return one;
    }
    if (one->val <= two->val)
    {
        one->next = mergeTwoLists(one->next, two);
        return one;
    }
    else if (one->val > two->val)
    {
        two->next = mergeTwoLists(one, two->next);
        return two;
    }
}

void printNode(ListNode* head)
{
    while (head != nullptr)
    {
        std::cout << head->val << std::endl;
        head = head->next;
    }
}

int main()
{
    ListNode* l2 = new ListNode{4, nullptr};
    ListNode* l1 = new ListNode{2, l2};
    ListNode* l0 = new ListNode{1, l1};

    ListNode* k2 = new ListNode{4, nullptr};
    ListNode* k1 = new ListNode{3, k2};
    ListNode* k0 = new ListNode{1, k1}; 

    printNode(mergeTwoLists(l0, k0));
}