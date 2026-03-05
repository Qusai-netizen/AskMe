#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

// Asistant Functions
enum enAgreement
{
    YES = 1,
    NO = 0
};

int random(int From, int To)
{
    return (rand() % (To - From + 1)) + From;
}

string readTxt(string message)
{
    string txt;
    cout << "\n"
         << message;
    cin >> txt;
    return txt;
}

int readNum(string message, int minVal, int maxVal, bool pos = 1)
{
    int num;
    do
    {
        cout << "\n"
             << message;
        cin >> num;
        if (pos && num < 0)
            continue;

    } while (num < minVal || num > maxVal);

    return num;
}

void uniqueMessage(string message)
{
    cout << "\n_________________________________\n";
    cout << "\n";
    cout << message;
    cout << "\n_________________________________\n";
}

struct stAccount;
struct stQues;
struct stDataBase;

struct stDataBase
{
    vector<stAccount> accounts;
    map<string, stQues> queses;
    vector<string> quesesIds;

    void updateQueses();
    void updateUsers();
    void deleteIdinQuesesIds(string id)
    {
        for (size_t i = 0; i < quesesIds.size(); ++i)
        {
            if (quesesIds[i] == id)
            {
                quesesIds.erase(quesesIds.begin() + i);
                return;
            }
        }
    }
    void loadQueses();
    void loadUsers();
};

struct stQues
{
    stDataBase *db;

    string quesOwnerId;

    string quesId;
    string ques;
    string answer;

    enAgreement isAnonymousQues;

    string ThreadParentQuesId;

    string toWhomId;

    stQues(stDataBase *_db = nullptr)
    {
        db = _db;
    }

    void genId(string &id)
    {
        do
        {
            id = to_string(random(1, 100000));
        } while (!isUniqueId(id));
        db->quesesIds.push_back(id);
    }

    bool isUniqueId(string &id)
    {
        for (const auto &q : db->quesesIds)
        {
            if (id == q)
                return 0;
        }
        return 1;
    }

    void fillQues()
    {
        if (cin.peek() == '\n')
            cin.ignore();
        cout << "\nEnter your question: ";
        getline(cin, ques);
    }

    void fillanswer()
    {
        if (cin.peek() == '\n')
            cin.ignore();
        cout << "\nEnter your answer: ";
        getline(cin, answer);
    }

    void fillIsAnonymousQues()
    {
        string answer;
        do
        {
            answer = readTxt("Do you want to ask in anonymous mode? (yes, no): ");
        } while (answer != "yes" && answer != "no");

        if (answer == "yes")
            isAnonymousQues = YES;
        else
            isAnonymousQues = NO;
    }
};

struct stAccount
{
    stDataBase *db;

    string id;
    string userName;
    string password;
    string fullName;
    string email;
    enAgreement allowsAnonymousQues;

    stAccount()
    {
        db = nullptr;
    }

    stAccount(stDataBase *_db)
    {
        db = _db;

        genId();
        fillUserName();
        password = getPassword();
        fillFullName();
        fillEmail();
        isAllowsAnonymousQues();
    }

    void genId()
    {
        do
        {
            id = to_string(random(1, 10000));
        } while (!isUniqueId());
    }

    bool isUniqueId()
    {
        for (const auto &a : db->accounts)
        {
            if (id == a.id)
                return 0;
        }
        return 1;
    }

    void fillUserName()
    {
        do
        {
            userName = readTxt("Enter user name. (No spaces): ");

            if (!isUniqueUserName())
                cout << "Used user name, try again.\n";
            else
                break;

        } while (true);
    }

    bool isUniqueUserName()
    {
        for (const auto &a : db->accounts)
        {
            if (userName == a.userName)
                return 0;
        }
        return 1;
    }

    static string getPassword()
    {
        return readTxt("Enter password: ");
    }

    void fillFullName()
    {
        fullName = readTxt("Enter your name: ");
    }

    void fillEmail()
    {
        do
        {
            email = readTxt("Enter an email: ");

            if (!isUniqueEmail())
                cout << "\nUsed email, try again.\n";
            else
                break;

        } while (true);
    }

    bool isUniqueEmail()
    {
        for (const auto &a : db->accounts)
        {
            if (email == a.email)
                return 0;
        }
        return 1;
    }

    void isAllowsAnonymousQues()
    {
        string answer;
        do
        {
            answer = readTxt("Do you allow anonymous qustions? (yes, no): ");
        } while (answer != "yes" && answer != "no");

        if (answer == "yes")
            allowsAnonymousQues = YES;
        else
            allowsAnonymousQues = NO;
    }
};

// stDataBase method definitions
void stDataBase::updateQueses()
{
    ofstream out("Questions.txt");

    for (auto &[key, value] : queses)
    {
        out << value.quesOwnerId << "\n";
        out << value.quesId << "\n";
        out << value.isAnonymousQues << "\n";
        out << value.ThreadParentQuesId << "\n";
        out << value.toWhomId << "\n";
        out << value.ques << "\n";
        out << value.answer << "\n";
    }
}

void stDataBase::updateUsers()
{
    ofstream out("Accounts.txt");

    for (const stAccount &a : accounts)
    {
        out << a.id << "\n";
        out << a.userName << "\n";
        out << a.password << "\n";
        out << a.fullName << "\n";
        out << a.email << "\n";
        out << a.allowsAnonymousQues << "\n";
    }
}

void stDataBase::loadQueses()
{
    queses.clear();
    quesesIds.clear();
    ifstream in("Questions.txt");
    if (!in)
        return;

    string temp;

    while (true)
    {
        stQues ques(&*this);
        if (!getline(in, ques.quesOwnerId))
            break;
        if (!getline(in, ques.quesId))
            break;
        if (!getline(in, temp))
            break;
        ques.isAnonymousQues = static_cast<enAgreement>(stoi(temp));
        if (!getline(in, ques.ThreadParentQuesId))
            break;
        if (!getline(in, ques.toWhomId))
            break;
        if (!getline(in, ques.ques))
            break;
        if (!getline(in, ques.answer))
            break;

        quesesIds.push_back(ques.quesId);
        queses[ques.quesId] = ques;
    }
}

void stDataBase::loadUsers()
{
    accounts.clear();
    ifstream in("Accounts.txt");
    if (!in)
        return;

    while (true)
    {
        stAccount a;
        if (!getline(in, a.id))
            break;
        if (!getline(in, a.userName))
            break;
        if (!getline(in, a.password))
            break;
        if (!getline(in, a.fullName))
            break;
        if (!getline(in, a.email))
            break;

        string temp;
        if (!getline(in, temp))
            break;
        a.allowsAnonymousQues = static_cast<enAgreement>(stoi(temp));

        accounts.push_back(a);
    }
}

struct stMain
{
    stDataBase db;
    string currentId;

    stMain()
    {
        db.loadQueses();
        db.loadUsers();
        controlMenu();
    }

    int accountIndexByUserName(string _userName)
    {
        for (size_t i = 0; i < db.accounts.size(); ++i)
        {
            if (db.accounts[i].userName == _userName)
                return i;
        }
        return -1;
    }

    int accountIndexById(string _id)
    {
        for (size_t i = 0; i < db.accounts.size(); ++i)
        {
            if (db.accounts[i].id == _id)
                return i;
        }
        return -1;
    }

    void printLoginMenu()
    {
        cout << "Menu\n";
        cout << "\t\t1: Login\n";
        cout << "\t\t2: Sign up\n";
    }

    unsigned short LoginMenuChoice()
    {
        return readNum("Enter a number in range (1, 2): ", 1, 2);
    }

    void signUp()
    {
        stAccount account(&db);
        db.accounts.push_back(account);
    }

    void login()
    {
        string password;
        do
        {
            string userName = readTxt("Enter your user name: ");
            int index = accountIndexByUserName(userName);

            if (index == -1)
                uniqueMessage("No user name called: " + userName);
            else
            {
                do
                {
                    password = readTxt("Enter your password: ");

                    if (db.accounts[index].password != password)
                        uniqueMessage("Wrong password.");
                    else
                        break;

                } while (true);

                currentId = db.accounts[index].id;
                break;
            }

        } while (true);
    }

    void LoginSignUpMenuControl()
    {
        printLoginMenu();
        unsigned short choice = LoginMenuChoice();

        if (choice == 1)
            login();
        else
        {
            signUp();
            db.updateUsers();
            LoginSignUpMenuControl();
        }
    }

    void logout()
    {
        currentId = "";
    }

    void askQues()
    {
        short choice;
        string toWhomId;
        int userInd;
        do
        {
            choice = readNum("Enter the Id of the user you want to ask or -1 to cancel: ", -1, 1000, 0);
            toWhomId = to_string(choice);
            userInd = accountIndexById(toWhomId);

            if (choice == -1)
                return;
            else if (userInd == -1)
                uniqueMessage("No id called: " + toWhomId);
            else
                break;
        } while (true);

        stQues ques(&db);
        ques.toWhomId = toWhomId;
        ques.quesOwnerId = currentId;

        if (db.accounts[userInd].allowsAnonymousQues == NO)
        {
            cout << "\nNote: you can't send anonymous questions to this id.\n";
            ques.isAnonymousQues = NO;
        }
        else
        {
            ques.fillIsAnonymousQues();
        }

        do
        {
            choice = readNum("For thread question: Enter the question id or -1 for a new question: ", -1, 1000, 0);
            string _quesId = to_string(choice);

            if (choice == -1)
            {
                ques.genId(ques.quesId);
                ques.fillQues();
                db.queses[ques.quesId] = ques;
                db.updateQueses();
                return;
            }
            else if (db.queses.find(_quesId) == db.queses.end())
                uniqueMessage("No id called: " + to_string(choice));
            else
            {
                ques.genId(ques.quesId);
                ques.fillQues();
                ques.ThreadParentQuesId = _quesId;
                db.queses[ques.quesId] = ques;
                db.updateQueses();
                return;
            }

        } while (true);
    }

    void printQuesToMe(stQues ques)
    {
        cout << "\n\n";
        if (ques.ThreadParentQuesId != "")
            cout << "\tThread";
        cout << "\tQustion Id (" << ques.quesId << ")";

        if (ques.isAnonymousQues == NO)
            cout << " from user Id(" << ques.quesOwnerId << ")";

        cout << "\tQuestion: " << ques.ques;
        cout << "\n";

        if (ques.ThreadParentQuesId != "")
            cout << "\tThread";
        cout << "\tAnswer: " << ques.answer;
    }

    void printMyQues(stQues ques)
    {
        cout << "\n\n";
        cout << "\tQustion Id (" << ques.quesId << ")";

        if (ques.isAnonymousQues == NO)
            cout << " !AQ ";

        cout << " to user id (" << ques.toWhomId << ")";
        cout << "\tQuestion: " << ques.ques;
        cout << "    Answer: ";
        if (ques.answer.empty())
            cout << "NOT ANSWERED YET.";
        else
            cout << ques.answer;
    }

    void printQuesesToMe()
    {
        if (db.queses.empty())
        {
            uniqueMessage("No questions yet.");
            return;
        }

        for (const string &_id : db.quesesIds)
        {
            if (db.queses[_id].toWhomId == currentId)
                printQuesToMe(db.queses[_id]);
        }
        db.updateQueses();
    }

    void printMyQueses()
    {
        if (db.queses.empty())
        {
            uniqueMessage("No questions yet.");
            return;
        }

        for (const string &_id : db.quesesIds)
        {
            if (db.queses[_id].quesOwnerId == currentId)
                printMyQues(db.queses[_id]);
        }
        db.updateQueses();
    }

    void answerQues()
    {
        short choice;
        do
        {
            choice = readNum("Enter the id of the question you want to answer or -1 to cancel: ", -1, 1000, 0);

            if (choice == -1)
                return;
            else
            {
                string _quesId = to_string(choice);
                if (db.queses.find(_quesId) == db.queses.end())
                    uniqueMessage("No qustion has this id.");
                else
                {
                    stQues &ques = db.queses[_quesId];
                    if (ques.toWhomId != currentId)
                    {
                        uniqueMessage("You can't answer other's questions.");
                        continue;
                    }
                    cout << "\n";
                    printQuesToMe(ques);
                    cout << "\n\n";

                    if (!ques.answer.empty())
                    {
                        uniqueMessage("Warning: Already answered. Answer will be updated.");
                    }
                    ques.fillanswer();
                    db.updateQueses();
                    return;
                }
            }
        } while (true);
    }

    void deleteQues()
    {
        short choice;
        do
        {
            choice = readNum("Enter the id of the question you want to delete or -1 to cancel: ", -1, 1000, 0);

            string _quesId = to_string(choice);

            if (_quesId == "-1")
                return;
            else if (db.queses.find(_quesId) == db.queses.end())
                uniqueMessage("No qustion has this id.");
            else
            {
                if (db.queses[_quesId].ThreadParentQuesId != "")
                {
                    if (currentId == db.queses[_quesId].quesOwnerId)
                    {
                        db.queses.erase(_quesId);
                        db.deleteIdinQuesesIds(_quesId);
                        db.updateQueses();
                    }
                    else
                        uniqueMessage("Sorry you can't delete others questions.");
                    return;
                }
                else
                {
                    if (currentId == db.queses[_quesId].quesOwnerId)
                    {
                        vector<string> toDelete;
                        for (const string &_id : db.quesesIds)
                        {
                            if (db.queses.count(_id) &&
                                db.queses[_id].ThreadParentQuesId == _quesId)
                            {
                                toDelete.push_back(_id);
                            }
                        }
                        db.queses.erase(_quesId);
                        db.deleteIdinQuesesIds(_quesId);
                        for (const string &_id : toDelete)
                        {
                            db.queses.erase(_id);
                            db.deleteIdinQuesesIds(_id);
                        }
                        db.updateQueses();
                    }
                    else
                        uniqueMessage("Sorry you can't delete others questions.");
                    return;
                }
            }
        } while (true);
    }

    void printUsers()
    {
        for (const stAccount &a : db.accounts)
        {
            cout << " ID: " << a.id;
            cout << "\tName: " << a.fullName;
            cout << "\n";
        }
    }

    void printFeed()
    {
        if (db.queses.empty())
        {
            uniqueMessage("No questions yet.");
            return;
        }

        for (const string &_id : db.quesesIds)
        {
            if (db.queses[_id].answer != "")
            {
                cout << "\n";
                if (db.queses[_id].ThreadParentQuesId != "")
                    cout << "Thread parent question id (" << db.queses[_id].ThreadParentQuesId << ") ";
                cout << "Question id (" << db.queses[_id].quesId << ") ";
                if (!db.queses[_id].isAnonymousQues)
                    cout << "from user id (" << db.queses[_id].quesOwnerId << ") ";
                cout << "to user id (" << db.queses[_id].toWhomId << ")";
                cout << "\t" << db.queses[_id].ques;
                cout << "\n";
                cout << "\tAnswer: " << db.queses[_id].answer;
            }
        }
    }

    void printMenu()
    {
        cout << "\n\nMenu:\n";
        cout << "\t1. Print questions to me.\n";
        cout << "\t2. Print questions from me.\n";
        cout << "\t3. Answer question.\n";
        cout << "\t4. Delete Question.\n";
        cout << "\t5. Ask question.\n";
        cout << "\t6. List system users.\n";
        cout << "\t7. Feed.\n";
        cout << "\t8. Logout.\n\n";
    }

    void controlMenu()
    {
        while (true)
        {
            if (currentId.empty())
                LoginSignUpMenuControl();
            printMenu();
            unsigned short choice = readNum("Enter number in renge (1, 8): ", 1, 8);

            switch (choice)
            {
            case 1:
                printQuesesToMe();
                break;
            case 2:
                printMyQueses();
                break;
            case 3:
                answerQues();
                break;
            case 4:
                deleteQues();
                break;
            case 5:
                askQues();
                break;
            case 6:
                printUsers();
                break;
            case 7:
                printFeed();
                break;
            case 8:
                logout();
                break;
            default:
                break;
            }
        }
    }
};

int main()
{
    srand((unsigned)time(NULL));
    stMain program;
    return 0;
}
