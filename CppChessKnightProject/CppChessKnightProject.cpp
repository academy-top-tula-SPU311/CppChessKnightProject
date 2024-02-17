#include <iostream>
#include <iomanip>

const int size{ 8 };
int board[size][size]{};

const int offset[8][2]
{
    { -2, 1},
    { -1, 2 },
    { 1, 2 },
    { 2, 1 },
    { 2, -1 },
    { 1, -2 },
    { -1, -2 },
    { -2, -1 }
};

void BoardPrint()
{
    for (int r{}; r < size; r++)
    {
        for (int c{}; c < size; c++)
            std::cout << std::setw(3) << board[r][c];
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool InBoard(int row, int column)
{
    return row >= 0 && row < size
        && column >= 0 && column < size;
}

int WeightCalculate(int row, int column)
{
    int weight{};

    for (int i{}; i < 8; i++)
    {
        int offsetRow = row + offset[i][0];
        int offsetColumn = column + offset[i][1];
        if (InBoard(offsetRow, offsetColumn))
        {
            if (board[offsetRow][offsetColumn] == 0)
                weight++;
        }
    }

    return weight;
}

int WeightMin(int weight[])
{
    int index;

    for (index = 0; index < 8; index++)
        if (weight[index])
            break;

    for (int i{ index + 1 }; i < 8; i++)
        if (weight[i])
            if (weight[index] >= weight[i])
                index = i;

    int indexesMin[8]{};
    int minSize{};

    for (int i{}; i < 8; i++)
    {
        if (weight[i] == weight[index])
            indexesMin[minSize++] = i;
    }
    index = indexesMin[rand() % minSize];

    return index;
}

void KnightRiding(int currentRow, int currentColumn)
{
    int step{};

    for (int r{}; r < size; r++)
        for (int c{}; c < size; c++)
            board[r][c] = 0;

    board[currentRow][currentColumn] = ++step;

    // 63 steps
    while (step < 63)
    {
        // weight varints cell
        int weight[8]{};


        // claculate weight
        for (int i{}; i < 8; i++)
        {
            int offsetRow = currentRow + offset[i][0];
            int offsetColumn = currentColumn + offset[i][1];

            if (InBoard(offsetRow, offsetColumn))
            {
                if (board[offsetRow][offsetColumn] == 0)
                    weight[i] = WeightCalculate(offsetRow, offsetColumn);
            }
        }

        // search min weight
        int weightMin = WeightMin(weight);

        currentRow += offset[weightMin][0];
        currentColumn += offset[weightMin][1];
        board[currentRow][currentColumn] = ++step;

        //BoardPrint();
    }


    // last step
    for (int i{}; i < 8; i++)
    {
        int offsetRow = currentRow + offset[i][0];
        int offsetColumn = currentColumn + offset[i][1];
        if (InBoard(offsetRow, offsetColumn))
            if (board[offsetRow][offsetColumn] == 0)
            {
                board[offsetRow][offsetColumn] = ++step;
                break;
            }
        
    }

    BoardPrint();
}

int main()
{
    int vars{};

    for (int r{}; r < size; r++)
        for (int c{}; c < size; c++)
        {
            std::cout << "-----" << (vars++ + 1) << "-----\n";
            KnightRiding(r, c);
            std::cout << "\n";
        }

    

    
}
