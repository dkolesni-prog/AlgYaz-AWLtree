#include <iostream>
//Задание:
//Реализовать шаблон структуры данных «АВЛ-дерево». Тип значения узла задаётся параметром
//        шаблона. Связь между узлами должна осуществляться с помощью указателей.
//Функции:
//1) конструктор; +
//2) деструктор;
//3) добавление элемента; +
//4) удаление элемента;
//5) печать на экран в виде вертикально-ориентированного дерева;
//6) вспомогательные функции (вращения, подсчёт высоты, другие функции, необходимые для
//                            полноценной работы). +
//
//Продемонстрировать работу структура данных на примере целочисленных элементов и элементов-
//пар с целочисленными ключами. Считать, что значения и ключи не повторяются.

template <class T>
struct node{
node <T>* left;
node <T>* right;
T key;
int heigth;
};

template <class T>
struct tree{
    node <T>* root;
};

template <class T>
void constructor (tree<T>* my_tree, T data){
    my_tree->root = new node<T>;
    my_tree->root->key = data;
    my_tree->root->heigth = 1;
    my_tree->root->left = nullptr;
    my_tree->root->right = nullptr;
}

template <class T>
int heigth (node<T>* my_node){
    if (my_node == nullptr){
        return 0;
    }
    else return my_node->heigth;
}

template <class T>
int balance_factor (node<T>* my_node){
   return heigth(my_node->right) - heigth(my_node->left);
}

template <class T>
void fix_heigth (node<T>* my_node){
    my_node->heigth = std::max (heigth(my_node->left) ,heigth(my_node-> right)) + 1;
}

//q = my_node
//p = temp

template <class T>
node<T>* tilt_left (node<T>* my_node){
    node<T>* temp = my_node->right;
    my_node->right = temp->left;
    temp->left = my_node;
    fix_heigth(my_node);
    fix_heigth(temp);
    return temp;
}

template <class T>
node<T>* tilt_right (node<T>* my_node){
    node<T>* temp = my_node->left;
    temp->left = my_node->right;
    my_node->right = temp;
    fix_heigth(temp);
    fix_heigth(my_node);
    return my_node;
}

template <class T>
node<T>* balance(node<T>* my_node) {
    fix_heigth(my_node);
    if (balance_factor(my_node) == 2) {
        if (balance_factor(my_node->right) < 0) {
            my_node->right = tilt_right(my_node->right);
        }
        return tilt_left(my_node);
    }
    if (balance_factor(my_node) == -2) {
        if (balance_factor(my_node->left) > 0) {
            my_node->left = tilt_left(my_node->left);
        }
        return tilt_right(my_node);
    }
    return my_node;
}

template <class T>
node<T>* insert(node<T>* my_node, T key) {
    if (my_node != nullptr)
    {
        node<T>* tmp = new node<T>;
        tmp->key = key;
        return tmp;
    }
    if (key < my_node->key) {
        my_node->left = insert(my_node->left, key);
    } else {
        my_node->right = insert(my_node->right, key);
    }
    return balance(my_node);
}

template <class T>
node<T>* find_min (node<T>* my_node){
    if (my_node->left != nullptr) return find_min(my_node->left);
   else return my_node;
}

template <class T>
node<T>* delete_min(node<T>* my_node) // удаление узла с минимальным ключом из дерева p
{
    if( my_node->left==0 )
        return my_node->right;
    my_node->left = delete_min(my_node->left);
    return balance(my_node);
}

template <class T>
node<T>* delete_key (node<T>* my_node, T key){
    if( my_node == nullptr) return nullptr; // если слева пусто
    if( key < my_node->key ) //если
        my_node->left = delete_key(my_node->left,key);
    else if( key > my_node->key )
        my_node->right = delete_key(my_node->right,key);
    else // если нашли key == my_node->key
    {
        node<T>* l = my_node->left;
        node<T>* r = my_node->right;
        delete my_node;
        if( r == nullptr ) return l;//если правого поддерева нет то вернем левое
        node<T>* min = find_min(r);// поиск минимального элемента в правом поддереве
        min->right = delete_min(r); // сохранение правой части минимума правой части
        min->left = l;//в левое поддерево минимума правой части присваемаем левую часть удаленного элемента
        return balance(min);
    }
    return balance(my_node);
}

template <class T>
node<T>* in_order (node<T>* my_node){
    if (my_node == nullptr) return nullptr;
    in_order(my_node->left);
    std::cout << my_node->key;
    in_order(my_node->right);
}



int main() {
    tree<int>* my_tree = new tree<int>;
    constructor(my_tree,0);
    insert(my_tree->root, 1);
    insert(my_tree->root, 2);
    insert(my_tree->root, -3);
    insert(my_tree->root, 4);
    insert(my_tree->root, -5);
    in_order(my_tree->root);
    delete_key(my_tree->root,0);
    in_order(my_tree->root);
    return 0;
}
