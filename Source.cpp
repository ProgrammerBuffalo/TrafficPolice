#include <iostream>
#include <string>
#include "TrafficPolice/Fine.h"
#include "TrafficPolice/AlcoholAbuseFine.h"
#include "TrafficPolice/OverSpeedFine.h"
#include "TrafficPolice/SocialDangerFine.h"

using namespace std;

template <typename T>
class List {
private:
   struct List_Node {
      T Data;
      List_Node* pNext = nullptr;
   };
   List_Node* head;
   size_t size;

   void List_pop_back() {
      auto ptrDelete = head;
      head = head->pNext;
      delete ptrDelete;
   }

   List_Node* Find_ptr(int index) {
      auto ptrCurrent = head;
      for (int i = 0; i < index; i++)
         ptrCurrent = ptrCurrent->pNext;
      return ptrCurrent;
   }

   int Find_ptr_index(List_Node*& ptr) {
      int index = 0;
      auto ptrCurrent = head;
      while (ptrCurrent != ptr) {
         ptrCurrent = ptrCurrent->pNext;
         index++;
      }
      return index;
   }

   void List_Reverse(List_Node* ptr) {
      if (ptr == nullptr)
         return;
      List_Reverse(ptr->pNext);
      cout << ptr->Data << " ";
   }

public:

   List() : size(0), head(nullptr) { }

   List(T data) {
      List_push_back(data);
   }

   ~List() {
      while (head != nullptr)
         List_pop(0);
   }

   void List_pop(int index) {
      if (index == 0) {
         List_pop_back();
      }
      else {
         auto ptrCurrent = head;
         for (int i = 0; i < index - 1; i++) {
            ptrCurrent = ptrCurrent->pNext;
         }
         auto ptrDelete = ptrCurrent->pNext;
         ptrCurrent->pNext = ptrDelete->pNext;
         delete ptrDelete;
      }
      size--;
   }

   void List_push_back(T& data) {
      List_Node* NewNode = new List_Node;
      NewNode->Data = data;
      NewNode->pNext = nullptr;
      if (head == nullptr)
         head = NewNode;
      else {
         auto ptrCurrent = Find_ptr(size - 1);
         ptrCurrent->pNext = NewNode;
      }
      size++;
   }

   void List_pop_by_data(T data) {
      auto ptrCurrent = head;
      for (int i = 0; i < size; i++) {
         if (ptrCurrent->Data == data) {
            ptrCurrent = ptrCurrent->pNext;
            List_pop(i--);
         }
         else
            ptrCurrent = ptrCurrent->pNext;
      }
   }

   void List_replace_data(T data, int index) {
      auto ptrCurrent = Find_ptr(index);
      ptrCurrent->Data = data;
   }

   void Reverse() {
      List_Reverse(head);
   }

   void List_Swap(int index1, int index2) {
      auto ptr1 = Find_ptr(index1 - 1);
      auto ptr2 = Find_ptr(index2 - 1);
      List_Node* temp;
      if (index1 + 1 != index2 && ptr1 != head) {
         temp = ptr2->pNext->pNext;
         ptr2->pNext->pNext = ptr1->pNext->pNext;
         ptr1->pNext->pNext = temp;
         temp = ptr2->pNext;
         ptr2->pNext = ptr1->pNext;
         ptr1->pNext = temp;
      }
      else if (index1 + 1 == index2 && ptr1 != head) {
         auto temp = ptr2->pNext->pNext;
         ptr2->pNext->pNext = ptr1->pNext;
         ptr1->pNext = ptr2->pNext;
         ptr2->pNext = temp;
      }
      else if (index1 + 1 != index2 && ptr1 == head) {
         auto temp = ptr2->pNext->pNext;
         ptr2->pNext->pNext = ptr1->pNext;
         ptr1->pNext = temp;
         temp = ptr2->pNext;
         ptr2->pNext = ptr1;
         head = temp;
      }
      else {
         auto temp = ptr1->pNext->pNext;
         ptr1->pNext->pNext = ptr2;
         head = ptr1->pNext;
         ptr1->pNext = temp;
      }
   }

   size_t GetSize() {
      return this->size;
   }

   T& operator[](int index) {
      return Find_ptr(index)->Data;
   }

   void Print() {
      auto ptrCurrent = head;
      while (ptrCurrent != nullptr) {
         cout << ptrCurrent->Data << " ";
         ptrCurrent = ptrCurrent->pNext;
      }
      cout << endl;
   }

   void operator=(List& source) {
      this->head = source.head;
      this->size = source.size;
      source.head = nullptr;
   }

   template <class T> friend ostream& operator<< (ostream& cout, List<T>& str);

};

template<class TKey, class TData>
class Tree {
private:
   struct Tree_Node {
      Tree_Node* parent = nullptr;
      Tree_Node* left = nullptr;
      Tree_Node* right = nullptr;
      TKey Key;
      TData Data;
   };

   Tree_Node* root;
   size_t count;

   void Print(Tree_Node* ptr) {
      if (ptr == nullptr || count == 0)
         return;
      if (ptr->left != nullptr)
         Print(ptr->left);
      cout << ptr->Key << ptr->Data << endl;
      if (ptr->right != nullptr)
         Print(ptr->right);
   }

   void Range_Print(Tree_Node* ptr, TKey key1, TKey key2 = "0") {
      if (ptr == nullptr || count == 0)
         return;
      if (ptr->left != nullptr)
         Range_Print(ptr->left, key1, key2);
      if (key1 <= ptr->Key && key2 >= ptr->Key)
         cout << ptr->Key << ptr->Data << endl;
      if (ptr->right != nullptr)
         Range_Print(ptr->right, key1, key2);
   }

   Tree_Node* MaxNode(Tree_Node* ptr) {
      if (ptr == nullptr)
         return nullptr;
      while (ptr->right != nullptr)
         ptr = ptr->right;
      return ptr;
   }

   Tree_Node* MinNode(Tree_Node* ptr) {
      if (ptr == nullptr)
         return nullptr;
      while (ptr->left != nullptr)
         ptr = ptr->left;
      return ptr;
   }

   Tree_Node* NextNode(Tree_Node* ptr) {
      if (ptr == nullptr)
         return nullptr;
      if (ptr->right != nullptr)
         MinNode(ptr->right);
      else {
         auto cursor = ptr;
         auto prev = cursor->parent;
         while (prev != nullptr && prev->left != cursor) {
            cursor = prev;
            prev = prev->parent;
         }
         return prev;
      }
   }

   Tree_Node* PrevNode(Tree_Node* ptr) {
      if (ptr == nullptr)
         return nullptr;
      if (ptr->left != nullptr)
         MaxNode(ptr->left);
      else {
         auto cursor = ptr;
         auto prev = cursor->parent;
         while (prev != nullptr && prev->right != cursor) {
            cursor = prev;
            prev = prev->parent;
         }
         return prev;
      }
   }

   Tree_Node* Search(TKey key) {
      auto cursor = root;
      while (cursor != nullptr) {
         if (cursor->Key == key)
            return cursor;
         else if (cursor->Key > key)
            cursor = cursor->left;
         else
            cursor = cursor->right;
      }
      return nullptr;
   }

   void Copy(Tree_Node* ptr)
   {
      if (ptr == nullptr)
         return;
      Tree_Add_Node(ptr->Key, ptr->Data);
      if (ptr->left != nullptr)
         Copy(ptr->left);
      if (ptr->right != nullptr)
         Copy(ptr->right);
   }

   void Remove(Tree_Node* node)
   {
      if (node == root)    root = nullptr;
      if (node == nullptr)    return;
      if (node->left != nullptr)    Remove(node->left);
      if (node->right != nullptr)    Remove(node->right);

      delete node;
      count--;
   }

public:

   Tree() : root(nullptr), count(0) {  }

   Tree(TKey key, TData data) {
      Tree_Add_Node(key, data);
   }

   Tree(const Tree& source) {
      this->Copy(source.root);
   }

   Tree(Tree&& source) {
      this->root = source.root;
      this->count = source.count;
      source.root = nullptr;
   }

   ~Tree() {
      if (count != 0 || root != nullptr)
         Remove(root);
   }

   void Tree_Add_Node(TKey key, TData& data) {
      Tree_Node* NewNode = new Tree_Node;
      NewNode->Data = data;
      NewNode->Key = key;
      if (root == nullptr || count == 0)
         root = NewNode;
      else {
         auto cursor = root;
         Tree_Node* prev = cursor;
         while (cursor != nullptr) {
            prev = cursor;
            if (key < cursor->Key)
               cursor = cursor->left;
            else
               cursor = cursor->right;
         }
         NewNode->parent = prev;
         if (key < prev->Key)
            prev->left = NewNode;
         else
            prev->right = NewNode;
      }
      count++;
   }

   void Tree_Node_pop(TKey key, Tree_Node* node = 0) {
      Tree_Node* cursor;
      if (node != 0)
         cursor = node;
      else
         cursor = Search(key);
      if (cursor == nullptr)
         return;
      auto prev = cursor;
      if (cursor->right != nullptr && cursor->left != nullptr) {
         cursor = MinNode(cursor->right);
         if (cursor != prev->right) {
            cursor->parent->left = nullptr;
            cursor->right = prev->right;
            prev->right->parent = cursor;
         }
         cursor->left = prev->left;
         prev->left->parent = cursor;
      }
      else if (cursor->right != nullptr || cursor->left != nullptr) {
         if (cursor->right != nullptr)
            cursor = cursor->right;
         else
            cursor = cursor->left;
         cursor->parent = prev->parent;
      }
      else {
         if (prev->parent != nullptr) {
            prev = cursor->parent;
            if (prev->right == cursor)
               prev->right = nullptr;
            else
               prev->left = nullptr;
            prev = cursor;
         }
         else
            cursor = nullptr;
      }
      if (prev != root) {
         if (prev->right != nullptr && prev->left != nullptr) {
            cursor->parent = prev->parent;
            if (prev->parent->Key > key)
               prev->parent->left = cursor;
            else
               prev->parent->right = cursor;
         }
      }
      else {
         if (cursor != nullptr)
            cursor->parent = nullptr;
         root = cursor;
      }
      delete prev;
      count--;
   }

   TKey Tree_MaxNode(TKey key) {
      return MaxNode(root)->Key;
   }

   TKey Tree_MinNode(TKey key) {
      return MinNode(root)->Key;
   }

   TKey Tree_NextKey(TKey key) {
      auto ptr = NextNode(Search(key));
      if (ptr != nullptr)
         return ptr->Key;
      return 0;
   }

   TKey Tree_PrevKey(TKey key) {
      auto ptr = PrevNode(Search(key));
      if (ptr != nullptr)
         return ptr->Key;
      return 0;
   }

   void Tree_Print() {
      Print(root);
   }

   void Tree_Range_Print(TKey key1, TKey key2 = "0") {
      Range_Print(root, key1, key2);
   }

   void Tree_Balance() {
      BalanceChecker(root);
   }

   void Tree_Print_Data(TKey key) {
      auto cursor = Search(key);
      if (cursor != nullptr) {
         cout << cursor->Key;
         cout << cursor->Data << endl;
      }
   }

   void Tree_Remove() {
      Remove(root);
      count = 0;
   }

   size_t Tree_GetSize() {
      return count;
   }

   TData& Tree_Find_Data(TKey key) {
      return Search(key)->Data;
   }

   Tree_Node* Tree_Find_Node(TKey key) {
      return Search(key);
   }

   Tree& operator=(Tree& source) {
      this->Remove(root);
      this->root = source.root;
      source.root = nullptr;
      this->count = source.count;
      return *this;
   }

};

class Ticket {
private:
    Fine fine;
   string vehicle;
public:

   Ticket() = default;

   Ticket(Fine* fine, string vehicle) {
      this->fine.Setfine(fine->GetString());
      this->fine.SetPoints(fine->GetPoints());
      this->vehicle = vehicle;
   }

   Fine& GetFine() {
      return this->fine;
   }

   string& GetVehicle() {
      return this->vehicle;
   }
};

class Region {
private:
   Tree<string, List<Fine>> region;

   List<Fine> Find_list(string name) {
      return region.Tree_Find_Data(name);
   }

   auto Find_Node(string name) {
      return region.Tree_Find_Node(name);
   }

   void Add_Region_Node(Ticket& ticket) {
      List<Fine> temp;
      temp.List_push_back(ticket.GetFine());
      region.Tree_Add_Node(ticket.GetVehicle(), temp);
   }

public:

   void Region_Add_Fine(Ticket& ticket) {
      auto cursor = Find_Node(ticket.GetVehicle());
      if (cursor == nullptr)
         Add_Region_Node(ticket);
      else
         cursor->Data.List_push_back(ticket.GetFine());
   }

   void Region_Remove_Fine(Ticket& ticket) {
      auto cursor = region.Tree_Find_Node(ticket.GetVehicle());
      if (cursor == nullptr)
         return;
      cursor->Data.List_pop_by_data(ticket.GetFine());
      if (cursor->Data.GetSize() < 1)
         region.Tree_Node_pop(ticket.GetVehicle(), cursor);
   }

   void Region_Remove_Node(string vehicle) {
      region.Tree_Node_pop(vehicle);
   }

   size_t Region_Get_Size() {
      return region.Tree_GetSize();
   }

   void Region_Vehicle_Find(string vehicle) {
      region.Tree_Print_Data(vehicle);
   }

   void Region_Print() {
      region.Tree_Print();
   }

   void Region_Print_Range(string name1, string name2 = "0") {
      region.Tree_Range_Print(name1, name2);
   }

};


class DataBase {
private:
   Tree<string, Region> database;

public:

   void Add_Fine(Ticket& ticket) {
      string temp = ticket.GetVehicle().substr(4, 2);
      auto cursor = database.Tree_Find_Node(temp);
      if (cursor == nullptr) {
         Region region;
         region.Region_Add_Fine(ticket);
         database.Tree_Add_Node(temp, region);
      }
      else {
         cursor->Data.Region_Add_Fine(ticket);
      }
   }

   void Remove_Node(string name) {
      auto cursor = database.Tree_Find_Node(name.substr(4, 2));
      if (cursor == nullptr)
         return;
      cursor->Data.Region_Remove_Node(name);

   }

   void Remove_Fine(Ticket& ticket) {
      string temp = ticket.GetVehicle().substr(4, 2);
      auto cursor = database.Tree_Find_Node(temp);
      if (cursor == nullptr)
         return;
      cursor->Data.Region_Remove_Fine(ticket);
      if (cursor->Data.Region_Get_Size() < 1)
         database.Tree_Node_pop(temp, cursor);
   }

   void Find_Vehicle(string vehicle) {
      string temp = vehicle.substr(4, 2);
      auto cursor = database.Tree_Find_Node(temp);
      if (cursor != nullptr)
         cursor->Data.Region_Vehicle_Find(vehicle);
   }

   void Print_Range_Database(string name1, string name2 = "0") {
      auto cursor = database.Tree_Find_Node(name1.substr(4, 2));
      if (cursor != nullptr)
         cursor->Data.Region_Print_Range(name1, name2);
   }

   void Print_DataBase() {
      database.Tree_Print();
   }

};

int operator == (Fine& fine1, Fine& fine2);

int operator < (Fine& fine1, Fine& fine2);

int operator > (Fine& fine1, Fine& fine2);

ostream& operator<<(ostream& cout, List<Fine>& fines);

ostream& operator<<(ostream& cout, Region& region);

void PrintInformation() {
   cout << "0: EXIT\n\n1: Add Vehicle (Add Database Node or Add Fine of vehicle)\n"
      << "2: Remove Vehicle (Remove Database Node)\n3: Remove fine (Remove List Node or Remove Node)\n"
      << "4: Find Vehicle\n5: Print all nodes of Database\n"
      << "6: Range print REGION of Database\n\n";
}

int main() {
   Fine* fine[] = { new SocialDangerFine, new OverSpeedFine, new AlcoholAbuseFine };
   DataBase base;
   string vehicle, vehicle_2;
   bool cycle = true;
   int key;
   while (cycle) {
      PrintInformation();
      cin >> key;
      system("cls");
      switch (key)
      {
      case 1: {
         cout << "Input vehicle: ";
         while (true) {
            cin >> vehicle;
            if (vehicle.size() == 6)
               break;
            else {
                cout << "Length should be 6! Please rewrite" << endl;
            }
         }
         cout << "Choose fine:\n1: Social Danger\n2: Over Speed\n3: Alcohol Abuse\n";
         while (true) {
            cin >> key;
            if (key > 0 && key < 4)
               break;
         }
         Ticket ticket(fine[key - 1], vehicle);
         base.Add_Fine(ticket);
         break;
      }
      case 2: {
         cout << "Input vehicle: ";
         while (true) {
            cin >> vehicle;
            if (vehicle.size() == 6)
                break;
            else {
                cout << "Length should be 6! Please rewrite" << endl;
            }
         }
         base.Remove_Node(vehicle);
         break;
      }
      case 3: {
         cout << "Input vehicle: ";
         while (true) {
            cin >> vehicle;
            if (vehicle.size() == 6)
                break;
            else {
                cout << "Length should be 6! Please rewrite" << endl;
            }
         }
         cout << "Choose fine:\n1: Social Danger\n2: Over Speed\n3: Alcohol Abuse\n";
         while (true) {
            cin >> key;
            if (key > 0 && key < 4)
               break;
         }
         Ticket ticket(fine[key - 1], vehicle);
         base.Remove_Fine(ticket);
         break;
      }
      case 4: {
         cout << "Input vehicle: ";
         while (true) {
            cin >> vehicle;
            if (vehicle.size() == 6)
                break;
            else {
                cout << "Length should be 6! Please rewrite" << endl;
            }
         }
         base.Find_Vehicle(vehicle);
         break;
      }
      case 5: {
         base.Print_DataBase();
         break;
      }
      case 6: {
         cout << "Input first vehicle: ";
         while (true) {
            cin >> vehicle;
            if (vehicle.size() == 6)
                break;
            else {
                cout << "Length should be 6! Please rewrite" << endl;
            }
         }
         cout << "Input second vehicle: ";
         cin >> vehicle_2;
         base.Print_Range_Database(vehicle, vehicle_2);
         break;
      }
      case 0: {
         cycle = false;
         break;
      }
      default: {
         cout << "Try again" << endl;
         break;
      }
      }
      cin.ignore();
      cout << "PRESS ENTER" << endl;
      getchar();
      system("cls");

   }
   return EXIT_SUCCESS;
}

int operator == (Fine& fine1, Fine& fine2) {
   return fine1.GetString().compare(fine2.GetString()) == 0;
}

int operator < (Fine& fine1, Fine& fine2) {
   return fine1.GetString().compare(fine2.GetString()) == -1;
}

int operator > (Fine& fine1, Fine& fine2) {
   return fine1.GetString().compare(fine2.GetString()) == 1;
}

ostream& operator<<(ostream& cout, List<Fine>& fines) {
   cout << " (Vehicle)\n";
   for (int i = 0; i < fines.GetSize(); i++) {
      cout << "\n" << i + 1 << ": " << fines[i].GetString() << " (Points: " << fines[i].GetPoints() << ")" << endl;
   }
   return cout;
}

ostream& operator<<(ostream& cout, Region& region) {
   cout << " (Region)\n";
   region.Region_Print();
   return cout;
}