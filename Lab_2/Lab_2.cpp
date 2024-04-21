#include <iostream>
#include <string>
using namespace std;

//Основные характеристики
struct Main_сharact
{
    string body_type; //Тип кузова
    string quantity_door; //Количество дверей
    string quantity_seat; //Количество мест
    string lenght; //Длина
    string width; //Ширина
    string height; //Высота
    string wheel_base; //Колесная база (мм)
    string equipment_base; //Снаряженная база автомобиля (кг)
    string full_base; //Полная база автомобиля (кг)
};

//Характеристики двигателя
struct Engine_сharact
{
    string type_engine; //Тип двигателя
    string working_volume; //Рабочий объем
    string compression_ratio; //Степень сжатия
    string max_power; //Максимальная мощность (л.с.)
    string max_torque; //Максимальный крутящий момент (Нм/об.мин)
};

//Скоростные характеристики
struct Speed_сharact
{
    string max_speed; //Максимальная скорость (км/ч)
    string average_consumption; //Средний расход топлива (л/100 км)
    string type_fuel; //Тип потребляемого топлива
};

//Узел дерева
struct Node
{
    string model; //Модель автомобиля
    Main_сharact* main = new Main_сharact;
    Engine_сharact* engine = new Engine_сharact;
    Speed_сharact* speed = new Speed_сharact;
    Node* left = nullptr;
    Node* right = nullptr;
};

//Бинарное дерево поиска
class Tree
{
private:
    Node* root = nullptr;
    Node* current = nullptr;
    // Добавление узла
    void insert_p(string name, Node* head)
    {
        if (more(head->model, name))
        {
            if (head->left == nullptr)
            {
                Node* new_node = new Node;
                new_node->model = name;
                head->left = new_node;
                write(new_node);
            }
            else
                insert_p(name, head->left);
        }
        else
        {
            if (head->right == nullptr)
            {
                Node* new_node = new Node;
                new_node->model = name;
                head->right = new_node;
                write(new_node);
            }
            else
                insert_p(name, head->right);
        }
    }
    // Сравнение названий двух моделей
    bool more(string head, string new_node)
    {
        bool flag = false;
        for (int i = 0; i < (min(head, new_node)).length(); i++)
        {
            if (head[i] < new_node[i])
                return false;
            else if (head[i] > new_node[i])
                return true;
        }
        if (head.length() == new_node.length())
            return false;
        if (head.length() > new_node.length())
            return true;
        else
            return false;
    }
    // Удаление узла
    Node* deleted_p(string name, Node* node, Node* pred_node)
    {
        if (node->model == name)
        {
            //Если нет потомков (лист)
            if (node->left == nullptr && node->right == nullptr)
            {
                //Если удаляемый узел - не корень
                if (pred_node != nullptr)
                {
                    if (pred_node->left == node)
                        pred_node->left = nullptr;
                    else
                        pred_node->right = nullptr;
                }
                else
                    root = nullptr;
                delete node;
                return nullptr;
            }
            //Если есть один потомок слева
            if (node->left != nullptr)
            {
                //Если удаляемый узел - корень
                if (pred_node == nullptr)
                {
                    Node* new_node = node->left;
                    delete node;
                    return new_node;
                }
                //Если удаляемый узел - не корень
                //Если пред. элемент ссылается этот слева
                if (pred_node->left == node)
                {
                    pred_node->left = node->left;
                    delete node;
                    return nullptr;
                }
                //Если пред. элемент ссылается этот справа
                else
                {
                    pred_node->right = node->left;
                    delete node;
                    return nullptr;
                }
            }
            //Если есть один потомок справа
            if (node->right != nullptr)
            {
                //Если удаляемый узел - корень
                if (pred_node == nullptr)
                {
                    Node* new_node = node->right;
                    delete node;
                    return new_node;
                }
                //Если удаляемый узел - не корень
                //Если пред. элемент ссылается этот слева
                if (pred_node->left == node)
                {
                    pred_node->left = node->right;
                    delete node;
                    return nullptr;
                }
                //Если пред. элемент ссылается этот справа
                else
                {
                    pred_node->right = node->right;
                    delete node;
                    return nullptr;
                }
            }
            //Если есть оба потомка
            if (node->left != nullptr && node->right != nullptr)
            {
                //Если текущий узел - корень
                if (pred_node == nullptr)
                {
                    //Если цепочка слева больше
                    if (search_max(node, 0) > search_max(node, 1))
                    {
                        Node* new_node = node;
                        Node* pred_new_node = node;
                        int n = 0;
                        new_node = new_node->left;
                        while (new_node->right != nullptr)
                        {
                            if (n++ == 0)
                                pred_new_node = pred_new_node->left;
                            else
                                pred_new_node = pred_new_node->right;
                            new_node = new_node->right;
                        }
                        new_node->left = node->left;
                        new_node->right = node->right;
                        pred_new_node->right = nullptr;
                        delete node;
                        return new_node;
                    }
                    //Если цепочка справа больше
                    if (search_max(node, 0) < search_max(node, 1))
                    {
                        Node* new_node = node;
                        Node* pred_new_node = node;
                        int n = 0;
                        new_node = new_node->right;
                        while (new_node->left != nullptr)
                        {
                            if (n++ == 0)
                                pred_new_node = pred_new_node->right;
                            else
                                pred_new_node = pred_new_node->left;
                            new_node = new_node->left;
                        }
                        new_node->left = node->left;
                        new_node->right = node->right;
                        pred_new_node->left = nullptr;
                        delete node;
                        return new_node;
                    }
                }
                //Если текущий узел - не корень
                if (pred_node != nullptr)
                {
                    //Если цепочка слева больше
                    if (search_max(node, 0) > search_max(node, 1))
                    {
                        Node* new_node = node;
                        Node* pred_new_node = node;
                        int n = 0;
                        new_node = new_node->left;
                        while (new_node->right != nullptr)
                        {
                            if (n++ == 0)
                                pred_new_node = pred_new_node->left;
                            else
                                pred_new_node = pred_new_node->right;
                            new_node = new_node->right;
                        }
                        new_node->left = node->left;
                        new_node->right = node->right;
                        pred_new_node->right = nullptr;
                        //Если пред. элемент ссылается этот слева
                        if (pred_node->left == node)
                            pred_node->left = new_node;
                        //Если пред. элемент ссылается этот справа
                        else
                            pred_node->right = new_node;
                        delete node;
                        return nullptr;
                    }
                    //Если цепочка справа больше
                    if (search_max(node, 0) < search_max(node, 1))
                    {
                        Node* new_node = node;
                        Node* pred_new_node = node;
                        int n = 0;
                        new_node = new_node->right;
                        while (new_node->left != nullptr)
                        {
                            if (n++ == 0)
                                pred_new_node = pred_new_node->right;
                            else
                                pred_new_node = pred_new_node->left;
                            new_node = new_node->left;
                        }
                        new_node->left = node->left;
                        new_node->right = node->right;
                        pred_new_node->left = nullptr;
                        //Если пред. элемент ссылается этот слева
                        if (pred_node->left == node)
                            pred_node->left = new_node;
                        //Если пред. элемент ссылается этот справа
                        else
                            pred_node->right = new_node;
                        delete node;
                        return nullptr;
                    }
                }
            }

        }
    }
    // Поиск макс цепочки для замены узла
    int search_max(Node* node, bool side)
    {
        int n = 0;
        //Если пошли по левой ветке
        if (!side)
        {
            while (node->right != nullptr)
            {
                node = node->right;
                n++;
            }
            return n;
        }
        //Если пошли по правой ветке
        if (side)
        {
            while (node->left != nullptr)
            {
                node = node->left;
                n++;
            }
            return n;
        }
    }
    // Поиск узла
    Node* search_p(string name,Node* node, Node* pred_node)
    {
        if (node->model == name)
        {
            return pred_node;
        }
        else
            if (node->left != nullptr)
            {
                Node* answer = search_p(name, node->left, node);
                if (answer != nullptr)
                    return answer;
            }
            if (node->right != nullptr)
            {
                Node* answer = search_p(name, node->right, node);
                if (answer != nullptr)
                    return answer;
            }
            return nullptr;
    }
    // Отчитка выделенной памяти
    bool delete_all(Node* root, Node* pred_root)
    {
        if (root == nullptr)
            return false;
        else if (root->left != nullptr)
            delete_all(root->left, root);
        else if (root->right != nullptr)
            delete_all(root->right, root);
        else
        {
            if (pred_root == nullptr)
            {
                delete root;
                return false;
            }
            if (pred_root->left == root)
                pred_root->left = nullptr;
            else
                pred_root->right = nullptr;
            delete root;
            return true;
        }
    }
    // Запись характеристик 
    void write(Node* node)
    {
        int n;
        string str;
        bool exit = true;
        while (exit)
        {
            cout << "1)Заполнить основные характеристики\n2)Заполнить характеристики двигателя\n3)Заполнить скоростные характеристики\n4)Закончить заполнение" << endl;
            cout << "Выбранный пункт: ";
            cin >> n;
            switch (n)
            {
            case 1:
                cout << "-----------------------------" << endl;
                cout << "Тип кузова: ";
                cin >> str;
                node->main->body_type = str;
                cout << "Количество дверей: ";
                cin >> str;
                node->main->quantity_door = str;
                cout << "Количество мест: ";
                cin >> str;
                node->main->quantity_seat = str;
                cout << "Длина: ";
                cin >> str;
                node->main->lenght = str;
                cout << "Ширина: ";
                cin >> str;
                node->main->width = str;
                cout << "Высота: ";
                cin >> str;
                node->main->height = str;
                cout << "Колесная база (мм): ";
                cin >> str;
                node->main->wheel_base = str;
                cout << "Снаряженная база автомобиля (кг): ";
                cin >> str;
                node->main->equipment_base = str;
                cout << "Полная база автомобиля (кг): ";
                cin >> str;
                node->main->full_base = str;
                cout << "-----------------------------" << endl;
                break;
            case 2:
                cout << "-----------------------------" << endl;
                cout << "Тип двигателя: ";
                cin >> str;
                node->engine->type_engine = str;
                cout << "Рабочий объем: ";
                cin >> str;
                node->engine->working_volume = str;
                cout << "Степень сжатия: ";
                cin >> str;
                node->engine->compression_ratio = str;
                cout << "Максимальная мощность (л.с.): ";
                cin >> str;
                node->engine->max_power = str;
                cout << "Максимальный крутящий момент (Нм/об.мин): ";
                cin >> str;
                node->engine->max_torque = str;
                cout << "-----------------------------" << endl;
                break;
            case 3:
                cout << "-----------------------------" << endl;
                cout << "Максимальная скорость (км/ч): ";
                cin >> str;
                node->speed->max_speed = str;
                cout << "Средний расход топлива (л/100 км): ";
                cin >> str;
                node->speed->average_consumption = str;
                cout << "Тип потребляемого топлива: ";
                cin >> str;
                node->speed->type_fuel = str;
                cout << "-----------------------------" << endl;
                break;
            case 4:
                exit = false;
                cout << "-----------------------------" << endl;
                break;
            default:
                cout << "Некорректный пункт" << endl;
                cout << "-----------------------------" << endl;
                break;
            }
        }
    }
    // Вывести все машины в автосалоне
    void write_all_p(Node* node)
    {
        bool flag = false;
        if (node->left != nullptr)
        {
            write_all_p(node->left);
            cout << node->model << endl;
            flag = true;
        }
        if (node->right != nullptr)
        {
            if (!flag)
                cout << node->model << endl;
            write_all_p(node->right);
        }
        if (node->left == nullptr && node->right == nullptr)
            cout << node->model << endl;
    }
public:
    Tree()
    {
        Node* root = nullptr;
    }
    ~Tree()
    {
        while (delete_all(root, nullptr));
    }
    void insert(string name)
    {
        cout << "-----------------------------" << endl;
        if (root == nullptr)
        {
            root = new Node;
            root->model = name;
            write(root);
        }
        else
        {
            insert_p(name, root);
        }
    }
    void deleted(string name)
    {
        cout << "-----------------------------" << endl;
        if (root == nullptr)
        {
            cout << "В автосолоне нет машин" << endl;
            cout << "-----------------------------" << endl;
            return;
        }
        Node* pred_node = search_p(name, root, nullptr);
        //Если узел это корень
        if (pred_node == nullptr)
        {
            Node* new_root = deleted_p(name, root, nullptr);
            if (new_root != nullptr)
                root = new_root;
        }
        //Если слева от предка
        else if (pred_node->left->model == name)
            deleted_p(name, pred_node->left, pred_node);
        //Если справа от предка
        else if (pred_node->right->model == name)
            deleted_p(name, pred_node->right, pred_node);
    }
    void search(string name)
    {
        cout << "-----------------------------" << endl;
        if (root == nullptr)
        {
            cout << "В автосалоне нет машин" << endl;
            cout << "-----------------------------" << endl;
            return;
        }
        current = search_p(name, root, nullptr);
        if (current == nullptr && name == root->model)
            current = root;
        else if (current == nullptr)
        {
            cout << "Элемент не найден" << endl;
            cout << "-----------------------------" << endl;
            return;
        }
        else if (current->left != nullptr && current->left->model == name)
            current = current->left;
        else if (current->right != nullptr && current->right->model == name)
            current = current->right;
        if (current != nullptr)
        {
            int n;
            bool exit = true;
            while (exit)
            {
                cout << "1)Вывести основные характеристики\n2)Вывести характеристики двигателя\n3)Вывести скоростные характеристики\n4)Заполнить характеристики\n5)Назад" << endl;
                cout << "Выбранный пункт: ";
                cin >> n;
                cout << "-----------------------------" << endl;
                switch (n)
                {
                case 1:
                    cout << "Тип кузова: " << current->main->body_type << endl;
                    cout << "Количество дверей: " << current->main->quantity_door << endl;
                    cout << "Количество мест: " << current->main->quantity_seat << endl;
                    cout << "Длина: "<< current->main->lenght << endl;
                    cout << "Ширина: " << current->main->width << endl;
                    cout << "Высота: " << current->main->height << endl;
                    cout << "Колесная база (мм): " << current->main->wheel_base << endl;
                    cout << "Снаряженная база автомобиля (кг): " << current->main->equipment_base << endl;
                    cout << "Полная база автомобиля (кг): " << current->main->full_base << endl;
                    cout << "-----------------------------" << endl;
                    break;
                case 2:
                    cout << "Тип двигателя: " << current->engine->type_engine << endl;
                    cout << "Рабочий объем: " << current->engine->working_volume << endl;
                    cout << "Степень сжатия: " << current->engine->compression_ratio << endl;
                    cout << "Максимальная мощность (л.с.): " << current->engine->max_power << endl;
                    cout << "Максимальный крутящий момент (Нм/об.мин): " << current->engine->max_torque << endl;
                    cout << "-----------------------------" << endl;
                    break;
                case 3:
                    cout << "Максимальная скорость (км/ч): " << current->speed->max_speed << endl;
                    cout << "Средний расход топлива (л/100 км): " << current->speed->average_consumption << endl;
                    cout << "Тип потребляемого топлива: " << current->speed->type_fuel << endl;
                    cout << "-----------------------------" << endl;
                    break;
                case 4:
                    write(current);
                    break;
                case 5:
                    exit = false;
                    break;
                default:
                    cout << "Некорректный пункт" << endl;
                    cout << "-----------------------------" << endl;
                    break;
                }
            }
        }
        current = root;
    }
    void write_all()
    {
        cout << "-----------------------------" << endl;
        if (root == nullptr)
        {
            cout << "В автосолоне нет машин" << endl;
            cout << "-----------------------------" << endl;
            return;
        }
        cout << "Список автомобилей:" << endl;
        write_all_p(root);
        cout << "-----------------------------" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    Tree a;
    bool quit = true;
    int n;
    string name;
    while (quit)
    {
        cout << "Меню:\n1)Добавить автомобиль\n2)Продать автомобиль\n3)Найти автомобиль\n4)Список автомобилей в наличии\n5)Выход" << endl;
        cout << "Выбранный пункт: ";
        cin >> n;
        switch (n)
        {
        case 1:
            cout << "Введите название модели: ";
            cin >> name;
            a.insert(name);
            break;
        case 2:
            cout << "Введите название модели: ";
            cin >> name;
            a.deleted(name);
            break;
        case 3:
            cout << "Введите название модели: ";
            cin >> name;
            a.search(name);
            break;
        case 4:
            a.write_all();
            break;
        case 5:
            quit = false;
            break;
        default:
            cout << "Некорректный пункт" << endl;
            cout << "-----------------------------" << endl;
            break;
        }
    }
}