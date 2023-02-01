// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: T10L 
// Names: MUHAMMAD AMIRUL HAIQAL BIN ZAMERI | MUHAMMAD AFIF JAZIMIN BIN IDRIS | LEE JUN YAO
// IDs: 1211104232 | 1211103419 | 1211103763 
// Emails: 1211104232@student.mmu.edu.my | 1211103419@student.mmu.edu.my | 1211103763@student.mmu.edu.my
// Phones: 011-53540207 | 010-5376195 | 011-23523686 
// ********************************************************* 

#include <iostream>
#include <iomanip>

// helper variables
int rows;
int columns;
int zombies;
int alienHealth;
int alienDamage;
int alienX, alienY;
int zombiesHealth[10];
int zombiesDamage[10];
int ranges[10];
int zombiesX[10];
int zombiesY[10];
char **grid;
// Define an array of characters
char characters[8] = {'^', 'v', '>', '<', 'h', 'p', 'r', ' '};

using namespace std;

void StartUp();
void customSetting();
void board();
void displayBoard();
void displayHealth();
void toLower(string &s);
bool boundary(int i, int j);
void alienMove(string direction);
void alienMove(string direction, int r, int c);
void zombieMove(int z);
void helpSection();
int Pause();
void arrow();
bool alienWin();
bool alienDead();
bool validPosition(int r, int c);
void hitpod(int r, int c);
void attack(int z, int r, int c, int range);
void resetPath();

int main()
{
    // Seed the random number generator
    srand(time(0));

    // Initial value
    rows = 5;
    columns = 9;
    zombies = 5;
    alienDamage = 0;

    StartUp();
    customSetting();

    alienHealth = (rand() % 5) * 50 + 150;
    grid = new char *[rows];
    for (int i = 0; i < rows; i++)
        grid[i] = new char[columns];

    board();

    string command;
    bool endGame = false;

    do
    {
        displayBoard();
        cout << "\nCommand > ";
        cin >> command;
        toLower(command);
        if (command == "up" || command == "down" || command == "left" || command == "right")
        {
            alienMove(command);
        }
        else if (command == "help")
        {
            helpSection(); // If command is help, will headed to helpSection function.
            Pause();
        }
        else if (command == "arrow")
        {
            arrow(); // If command is arrow, will headed to arrow function.
            Pause();
        }
        else if (command == "save")
        {
            // will implement in part 2
            Pause();
        }
        else if (command == "load")
        {
            // will implement in part 2
            Pause();
        }
        else if (command == "quit")
        {
            cout << "\nQuiting Game...\n";
            Pause();
            endGame = true;
        }
        else
            cout << "\n\nInvalid Command!!\n\n";

        if (alienWin())
        {
            cout << "Alien Wins!\n\n";
            endGame = true;
        }
        else if (alienDead())
        {
            cout << "Alien Died (^,^)";
            endGame = true;
        }

    } while (!endGame);

    system("pause");

    return 0;
}

void resetPath()
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (grid[i][j] == '.') // If a cell contains a period ('.'), it is replaced with a randomly selected character from the array "characters" with 8 elements. The random character is selected using the "rand() % 8" expression, which returns a random integer between 0 and 7.
                grid[i][j] = characters[rand() % 8];
        }
    }
}

void attack(int z, int r, int c, int range) // Checks if the alien is within the zombie's attack range by calculating the absolute difference between the alien's row and column coordinates and the zombie's coordinates and comparing it to the range
{
    if ((abs(r - alienX) <= range) && (abs(c - alienY) <= range))
    {
        cout << "Zombie " << z + 1 << " attacks Alien with damage " << zombiesDamage[z] << "\n";
        alienHealth -= zombiesDamage[z];
    }
    else
    {
        cout << "Zombie cannot attack. Alien is out of range.\n\n";
    }
}

void hitpod(int r, int c) // Keeps track of the index of the zombie closest to the hitpod, and that zombie takes damage of 10. The health of each zombie is stored in an array named "zombiesHealth"
{
    int i, minDistance = 99, minDisIndex, distance;
    for (i = 0; i < zombies; i++)
    {
        distance = (abs(zombiesX[i] - r) + abs(zombiesY[i] - c));
        if (minDistance > distance)
        {
            minDistance = distance;
            minDisIndex = i;
        }
    }

    cout << "Zombie " << minDisIndex + 1 << " is closest to the zombie. It gets a damage of 10.\n\n";
    zombiesHealth[minDisIndex] -= 10;
    if (zombiesHealth[minDisIndex] <= 0) // If the damage taken reduces a zombie's health to 0 or less, the function outputs a message indicating that the zombie has died and updates its position to (-1, -1)
    {
        cout << "Zombie " << minDisIndex + 1 << "Died.\n\n";
        zombiesX[minDisIndex] = -1;
        zombiesY[minDisIndex] = -1;
    }
}

bool validPosition(int r, int c)
{
    if (alienX == r && alienY == c)
        return false;

    for (int i = 0; i < zombies; i++)
        if (zombiesX[i] == r && zombiesY[i] == c)
            return false;
    return true;
}

void zombieMove(int z)
{
    int num;
    cout << "\nZombie " << z + 1 << "\'s turn.\n";
    while (true)
    {
        num = rand() % 4;
        ////Checks if the move is within the grid boundary and if the new position is not occupied by the alien or another zombie
        if (num == 0 && !boundary(zombiesX[z] - 1, zombiesY[z]) && validPosition(zombiesX[z] - 1, zombiesY[z]))
        { // If the move is valid, the grid is updated, the zombie's new position is recorded
            grid[zombiesX[z] - 1][zombiesY[z]] = grid[zombiesX[z]][zombiesY[z]];
            grid[zombiesX[z]][zombiesY[z]] = ' ';
            zombiesX[z]--;
            cout << "\nZombie " << z + 1 << " moves up\n";
            break;
        }
        else if (num == 1 && !boundary(zombiesX[z] + 1, zombiesY[z]) && validPosition(zombiesX[z] + 1, zombiesY[z]))
        {
            grid[zombiesX[z] + 1][zombiesY[z]] = grid[zombiesX[z]][zombiesY[z]];
            grid[zombiesX[z]][zombiesY[z]] = ' ';
            zombiesX[z]++;
            cout << "\nZombie " << z + 1 << " moves down\n";
            break;
        }
        else if (num == 2 && !boundary(zombiesX[z], zombiesY[z] - 1) && validPosition(zombiesX[z], zombiesY[z] - 1))
        {
            grid[zombiesX[z]][zombiesY[z] - 1] = grid[zombiesX[z]][zombiesY[z]];
            grid[zombiesX[z]][zombiesY[z]] = ' ';
            zombiesY[z]--;
            cout << "\nZombie " << z + 1 << " moves left\n";
            break;
        }
        else if (num == 3 && !boundary(zombiesX[z], zombiesY[z] + 1) && validPosition(zombiesX[z], zombiesY[z] + 1))
        {
            grid[zombiesX[z]][zombiesY[z] + 1] = grid[zombiesX[z]][zombiesY[z]];
            grid[zombiesX[z]][zombiesY[z]] = ' ';
            zombiesY[z]++;
            cout << "\nZombie " << z + 1 << " moves right\n";
            break;
        }
    }

    attack(z, zombiesX[z], zombiesY[z], ranges[z]); // attack on the alien is attempted with the range z
}

void alienMove(string direction) // moves the alien in a particular direction (up, down, left, or right) based on the input string argument. The function first resets the alien's trail, then moves the alien in the given direction by calling the alienMove function and passing it the direction, the new x-coordinate and y-coordinate. After the alien move, the trail is reset again and the zombie moves are executed one by one.
{
    alienDamage = 0;
    if (direction == "up")
        alienMove(direction, alienX - 1, alienY);
    else if (direction == "down")
        alienMove(direction, alienX + 1, alienY);
    else if (direction == "left")
        alienMove(direction, alienX, alienY - 1);
    else if (direction == "right")
        alienMove(direction, alienX, alienY + 1);
    alienDamage = 0;
    cout << "Alien Move Ends. Reseting trail...\n\n";
    Pause();
    resetPath();
    for (int i = 0; i < zombies; i++)
    {
        if (zombiesHealth[i] > 0)
        {
            displayBoard();
            zombieMove(i);
            Pause();
        }
    }
}

void alienMove(string direction, int r, int c)
{
    if (boundary(r, c))
        return; // If the current position is outside the boundaries of the grid, the function returns

    int tr, tc;
    displayBoard();
    if (direction == "up")
        cout << "\nAlien moves Up\n";
    else if (direction == "down")
        cout << "\nAlien moves Down\n";
    else if (direction == "right")
        cout << "\nAlien moves Right\n";
    else if (direction == "left")
        cout << "\nAlien moves Left\n";

    tr = alienX;
    tc = alienY;
    grid[alienX][alienY] = '.';
    alienX = r;
    alienY = c;
    // Current state of the grid, and updates the alien's position and properties (e.g., health, damage) based on the contents of the grid at the new position.
    if (grid[r][c] == '^')
    {
        grid[r][c] = 'A';
        cout << "Alien finds a arrow in upward direction.\n";
        cout << "Alien Damage is increased by 20.\n";
        Pause();
        alienDamage += 20;
        alienMove("up", r - 1, c);
        return;
    }

    else if (grid[r][c] == '>')
    {
        grid[r][c] = 'A';
        cout << "Alien finds a arrow in Right direction.\n";
        cout << "Alien Damage is increased by 20.\n";
        Pause();
        alienDamage += 20;
        alienMove("right", r, c + 1);
        return;
    }

    else if (grid[r][c] == 'v')
    {
        grid[r][c] = 'A';
        cout << "Alien finds a arrow in Downward direction.\n";
        cout << "Alien Damage is increased by 20.\n";
        Pause();
        alienDamage += 20;
        alienMove("down", r + 1, c);
        return;
    }

    else if (grid[r][c] == '<')
    {
        grid[r][c] = 'A';
        cout << "Alien finds a arrow in left direction.\n";
        cout << "Alien Damage is increased by 20.\n";
        Pause();
        alienDamage += 20;
        alienMove("left", r, c - 1);
        return;
    }

    else if (grid[r][c] == 'h')
    {
        cout << "Alien finds a health.\n20 is Added to Alien Health.\n";
        alienHealth += 20;
    }

    else if (grid[r][c] == 'p')
    {
        cout << "Alien finds a pod.\nInflicts 10 damage to nearest Zombie.\n";
        hitpod(r, c);
    }

    else if (grid[r][c] == 'r')
    {
        cout << "Alien finds a rock.\n";
        int a = rand() % 3;
        if (a == 0)
        {
            cout << "Rock was hiding a Pod beneath.\n";
            grid[r][c] = 'p';
        }
        else if (a == 1)
        {
            cout << "Rock was hiding a Health beneath.\n";
            grid[r][c] = 'h';
        }
        else
        {
            cout << "Rock was hiding Nothing beneath.\n";
            grid[r][c] = ' ';
        }
        alienX = tr;
        alienY = tc;
        grid[alienX][alienY] = 'A';
        return;
    }
    // If the new position contains a zombie, the alien will attack and potentially kill the zombie, reducing its health by the alien's damage
    else if (grid[r][c] >= '1' && grid[r][c] <= '9')
    { // grid[r][c] >= '1' && grid[r][c] <= '9' is zombies
        cout << "Alien hits a Zombie.\n";
        cout << "Alien Attacks with damage " << alienDamage << "\n";
        zombiesHealth[grid[r][c] - '0' - 1] -= alienDamage;
        if (zombiesHealth[grid[r][c] - '0' - 1] <= 0)
        {
            cout << "Zombie " << grid[r][c] << " Died.\nAlien continues to move.\n\n";
            zombiesX[grid[r][c] - '0' - 1] = -1;
            zombiesY[grid[r][c] - '0' - 1] = -1;
        }
        else
        {
            alienX = tr;
            alienY = tc;
            grid[alienX][alienY] = 'A';
            return;
        }
    }
    else
        cout << "Alien finds an empty space.\n\n";

    grid[r][c] = 'A'; // move the alien in the same direction until it reaches an empty space or an object that stops its movement.
    Pause();
    if (direction == "up")
        alienMove(direction, r - 1, c);
    else if (direction == "down")
        alienMove(direction, r + 1, c);
    else if (direction == "left")
        alienMove(direction, r, c - 1);
    else if (direction == "right")
        alienMove(direction, r, c + 1);
}
// If all zombies have zero health, the function returns true, indicating that the aliens have won.
bool alienWin()
{
    for (int i = 0; i < zombies; i++)
    {
        if (zombiesHealth[i] > 0)
        {
            return false;
        }
    }
    return true;
}

bool alienDead()
{ // check the health of alien is zero or not
    if (alienHealth <= 0)
        return true;
    return false;
}

bool boundary(int i, int j)
{
    return (i < 0 || j < 0 || i >= rows || j >= columns);
}

void arrow()
{
    int r, c;
    string direction;
    do
    {
        cout << "\nEnter row: ";
        cin >> r;

        if (cin.fail() || r < 1 || r > rows)
        {
            cin.clear();
            cin.ignore();
            cout << "\nInvalid Input!! Number of rows are " << rows << ".\n";
        }
    } while (r < 1 || r > rows);

    do
    {
        cout << "\nEnter column: ";
        cin >> c;

        if (cin.fail() || c < 1 || c > columns)
        {
            cin.clear();
            cin.ignore();
            cout << "\nInvalid Input!! Number of columns are " << columns << ".\n";
        }
    } while (c < 1 || c > columns);

    cin.ignore();
    do
    {
        cout << "\nEnter direction: ";
        cin >> direction;

        toLower(direction);
        if (direction != "up" && direction != "down" && direction != "left" && direction != "right")
        {
            cout << "\nInvalid Input!!\n";
        }
        // The direction input is also validated to make sure it's either "up", "down", "left", or "right"
    } while (direction != "up" && direction != "down" && direction != "left" && direction != "right");
    // The arrow is then fired in the specified direction if the grid at the specified position contains an arrow
    if (grid[r - 1][c - 1] == '^' || grid[r - 1][c - 1] == '<' || grid[r - 1][c - 1] == '>' || grid[r - 1][c - 1] == 'v')
    {
        if (direction == "up")
            grid[r - 1][c - 1] = '^';
        else if (direction == "down")
            grid[r - 1][c - 1] = 'v';
        else if (direction == "left")
            grid[r - 1][c - 1] = '<';
        else if (direction == "right")
            grid[r - 1][c - 1] = '>';
    }
    else
    {
        cout << "\nThis is not an arrow.\n\n"; // Doesn't contain an arrow message
    }
    cin.ignore();
}

void StartUp()
{
    cout << "|>>>>>>>>>>>>>>>>o<<<<<<<<<<<<<<<<|" << endl;
    cout << "|   Welcome To Alien VS Zombie!   |" << endl;
    cout << "|>>>>>>>>>>>>>>>>o<<<<<<<<<<<<<<<<|" << endl
         << endl;
    cout << "Press Enter to continue . . .";
    cin.ignore();
    cout << " " << endl;
}

void customSetting()
{
    cout << "-----------------------" << endl;
    cout << " Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << " " << endl;
    cout << "Board Rows: " << rows << endl;
    cout << "Board Columns: " << columns << endl;
    cout << "Zombie Count: " << zombies << endl
         << endl;

    char answer;
    cout << "Do you wish to change default setting? (y/n) => ";
    cin >> answer;
    cout << " " << endl;

    // check if user wants to change default setting
    if (tolower(answer) == 'y')
    { // tolower() is to convert input to lowercase

        cout << "Enter the number of rows: ";
        cin >> rows;
        while (rows % 2 == 0)
        {
            cout << " " << endl;
            cout << "Number of rows cannot be in even number." << endl
                 << endl;
            cout << "Enter the number of rows: ";
            cin >> rows;
        }

        cout << "Enter the number of columns: ";
        cin >> columns;
        while (columns % 2 == 0)
        {
            cout << " " << endl;
            cout << "Number of columns cannot be in even number." << endl
                 << endl;
            cout << "Enter the number of columns: ";
            cin >> columns;
        }

        cout << "Enter number of zombie(s):";
        cin >> zombies;

        while (zombies > 10)
        {
            cout << " " << endl;
            cout << "Number of zombie must below than 10" << endl
                 << endl;
            cout << "Enter number of zombie(s):";
            cin >> zombies;
        }
    }
}

void helpSection()
{
    cout << "\n\tCommands\n";
    cout << "up    - Alien to move up\n";
    cout << "down  - Alien to move down\n";
    cout << "left  - Alien to move left\n";
    cout << "right - Alien to move right\n";
    cout << "arrow - Change the direction of an arrow\n";
    cout << "help  - Display these user commands\n";
    cout << "save  - Save the game\n";
    cout << "load  - Load a game\n";
    cout << "quit  - Quit the game\n\n";
}

void displayBoard()
{
    // Print top row of "+" and "-"
    cout << setw(4) << " ";
    for (int i = 1; i <= columns; i++)
    {
        cout << "+"
             << " - ";
    }
    cout << "+" << endl;

    // Print the grid with your specified characters
    for (int i = 1; i <= rows; i++)
    {
        cout << setw(4) << i;
        for (int j = 1; j <= columns; j++)
        {
            cout << "|"
                 << " " << grid[i - 1][j - 1] << " ";
        }
        cout << "|" << endl;

        // Print row of "+" and "-"
        cout << setw(5) << "+";
        for (int j = 1; j <= columns; j++)
        {
            cout << " - "
                 << "+";
        }
        cout << endl;
    }

    // Print column numbers below grid
    cout << setw(5) << " ";
    for (int i = 1; i <= columns; i++)
    {
        cout << setw(2) << i << setw(2) << ' ';
    }
    cout << endl;
    displayHealth();
}

void board()
{
    // calculate the middle row and column
    int middleRow = (rows - 1) / 2;
    int middleColumn = (columns - 1) / 2;
    alienX = middleRow;
    alienY = middleColumn;

    // randomly place the zombies on the board
    int x, y;
    for (int i = 0; i < zombies; i++)
    {
        x = rand() % rows;
        y = rand() % columns;
        if (!validPosition(x, y))
        {
            i--;
            continue;
        }
        zombiesX[i] = rand() % rows;
        zombiesY[i] = rand() % columns;
    }

    for (int i = 0; i < zombies; i++)
    {
        zombiesHealth[i] = (rand() % 3) * 50 + 150;
        zombiesDamage[i] = (rand() % 3) * 5 + 5;
        ranges[i] = (rand() % (rows - 1) - 1) + 1;
    }

    // Print the grid with your specified characters
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            // Use the modulo operator to cycle through the characters array
            char c = characters[rand() % 8];
            grid[i][j] = c;
            if (i == middleRow && j == middleColumn)
            {
                grid[i][j] = 'A';
            }
            // check if the current cell is a zombies
            for (int k = 0; k < zombies; k++)
            {
                if (i == zombiesX[k] && j == zombiesY[k])
                {
                    grid[i][j] = k + 1 + '0';
                }
            }
        }
    }

    // Print column numbers below grid
    cout << setw(5) << " ";
    for (int i = 1; i <= columns; i++)
    {
        cout << setw(2) << i << setw(2) << ' ';
    }
    cout << endl;
}

void displayHealth() // Displays the health, damage and range of the alien and the zombies
{
    cout << "\nAlien :     Health " << alienHealth << "\tDamage " << alienDamage << endl;
    for (int i = 0; i < zombies; i++)
    {
        cout << "Zombie " << i + 1 << ":  "
             << " Health " << zombiesHealth[i] << ", Damage " << zombiesDamage[i] << ", Range " << ranges[i] << endl;
    }
}

void toLower(string &s)
{
    int i = 0, l = s.length();
    for (i = 0; i < l; i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] -= 32;
}

int ClearScreen()
{
#if defined(_WIN32)
    return std::system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    return std::system("clear");
#endif
}

int Pause() // Pause the game until the user presses any key
{
#if defined(_WIN32)
    return std::system("pause");
#elif defined(__linux__) || defined(__APPLE__)
    return std::system(R"(read -p "Press any key to continue . . . " dummy)");
#endif
}

