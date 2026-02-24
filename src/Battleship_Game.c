#include <stdio.h>
#include <stdlib.h>

int* r;
int* c;
int flag;

void displayTheWelcomeScreen(){
    printf ("----------------------------------------------------------------------------------------------------------------------\n\n");
    printf("                                    Amiral Battı Oyununa Hoş geldiniz. \n");
    printf("Oyunun kuralları aşağıdaki gibidir: \n");
    printf("- Oyun 2 kişi ile oynanmaktadır. \n");
    printf("- Player1 ve Player2 kendi oyun tahtasına gemilerini yerleştirir. \n");
    printf(" - int main() içinde default olarak 1 Admiral(Uzunluk=3), 3 Destroyer(Uzunluk=2), 4 Boat(Uzunluk=1) tanımlanmıştır.  \n");
    printf("  - Aşağıdaki şekilde yeni gemiler oyuna dahil edilebilir.  \n");
    printf("   - placeShip(player1Board, 6, 'N', &shipLengthsCounter); placeShip(player2Board, 6, 'N', &shipLengthsCounter);  6(Yeni geminin uzunluğu) N(Yeni geminin sembolu) \n");
    printf("   - İki oyuncunun eşit koşullarda rekabet edebilmesi için iki oyuncunun da sahip olduğu gemi uzunlukları eşit olmak zorundadır. Oyun bu şekilde tasarlanmıştır. Eğer eşit uzunlukta yerleştirme yapılmazsa hata alınacaktır. \n");
    printf("    - Ör: Player1 gemi uzunlukları: 4 5 3 2 1 (Toplam 15), Player2 gemi uzunlukları: 4 4 4 3 (Toplam 15) Oyun hata vermez. / 4 4 4 1 (Toplam 13) Oyun Hata verir \n");
    printf("    - Bu sebeple lütfen main() kısmı içinde buna dikkat ederek gemi ekleme çıkarma yapınız. \n");
    printf("- Oyun başladığında oyun alanının büyüklüğü kullanıcıya sorulur ROW ve COLUMN olarak girdi almanız beklenir. \n");
    printf("- Bu aşamadan sonra sırasıyla Player1 ve Player2 gemilerini yerleştirir.  \n");
    printf(" - Gemileri yerleştirirken kullanıcıdan 3 parametre girmesi beklenir (ROW, COLUMN, DIRECTION) \n");
    printf("  - R = Right, L = Left, A = Above, D = Down \n");
    printf("  - 0 0 R index'ine Amiral geminizi yerleştiriyorsanız program öncelikle bu parametrelerin Valid olup olmadığını sorgular. \n");
    printf("  - Ör: 0 0 K girdiğinizde hata verir çünkü K tanımsızdır. Ayrıca 0 0 R hata vermezken 0 0 L hata verir çünkü (0 0) (0 -1) (0 -2) index'lerine sola doğru bir yerleştirme geçersizdir.");
    printf("  - Program oyuncuları kendi tahtalarında gemi olan yere gemi yerleştirmelerini engelleyecek şekilde tasarlanmıştır. \n");
    printf("- Bu aşamalardan sonra oyun Player1'den başlayarak attack yapılmasını sağlar. \n");
    printf(" - Player1, Player2'nin gemilerini yerleştirdiği tahtaya atış yapar. Player2, Player1'in gemilerini yerleştirdiği tahtaya atış yapar. \n");
    printf(" - Attack sonrasında tahta Hit!(H) veya Miss!(M) ile  işaretlenir. Eğer daha saldırılmamışsa X ile işaretlenmiştir. \n");
    printf("- Kullanıcıların görebileceği iki tane counter tasarlanmıştır. İlki oyunda kaç tane geçerli hamle yapıldığı, ikincisi oyuncunun kaç tane hit yaptığını hesaplamaktadır. Bu değerler oyun esnasında ekrana yazdırılır. \n");
    printf("- Oyunculardan herhangi birisi karşısındaki rakibin bütün gemi lokasyonlarını vurana kadar oyun bu şekilde devam eder. Oyun bitiminde hangi oyuncunun oyunu kazandığı yazdırılır. Ve oyun sonlanır. \n\n");
    printf ("----------------------------------------------------------------------------------------------------------------------\n");
}

void printBoard(char board[*r][*c]) {
    printf("     ");
    for (int i = 0; i < *c; i++) {
        printf("%c|", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < *r; i++) {
        if(i<=9){
            printf("0%d |", i);
        }else{
            printf("%d |", i);
        }
        for (int j = 0; j < *c; j++) {
            printf(" %c", board[i][j]);
        }
        printf("\n");
    }
}

int isValidIndex(int row, int col) {
    return (row >= 0 && row < *r && col >= 0 && col < *c);
}

void placeShip(char board[*r][*c], int shipLength, char symbol, int* shipLengthsCounter) {
    int row, col;
    char direction;

    do {
        printf("Place your %d-length %c (row, col, direction - R/L/D/A): ", shipLength, symbol);
        scanf("%d %d %c", &row, &col, &direction);
        flag = 0;

        if (!isValidIndex(row, col)) {
            printf("Invalid indices. Try again.\n");
            continue;
        }

        if (direction == 'R' && col + shipLength > *c) {
            printf("Invalid placement. Out of bounds. Try again.\n");
            continue;
        } else if (direction == 'L' && col - shipLength + 1 < 0) {
            printf("Invalid placement. Out of bounds. Try again.\n");
            continue;
        } else if (direction == 'D' && row + shipLength > *r) {
            printf("Invalid placement. Out of bounds. Try again.\n");
            continue;
        } else if (direction == 'A' && row - shipLength + 1 < 0) {
            printf("Invalid placement. Out of bounds. Try again.\n");
            continue;
        }

        if (direction == 'R') {
            for (int i = 0; i < shipLength; i++) {
                if (board[row][col + i] != 'X') {
                    flag = 1;
                }
            }
            if(flag == 1) {
                printf("Invalid placement. Try again.\n");
                continue;
            }

            for (int i = 0; i < shipLength; i++) {
                board[row][col + i] = symbol;
            }
            (*shipLengthsCounter) += shipLength;
        } else if (direction == 'L') {
            for (int i = 0; i < shipLength; i++) {
                if (board[row][col - i] != 'X') {
                    flag = 1;
                }
            }
            if(flag == 1) {
                printf("Invalid placement. Try again.\n");
                continue;
            }

            for (int i = 0; i < shipLength; i++) {
                board[row][col - i] = symbol;
            }
            (*shipLengthsCounter) += shipLength;
        } else if (direction == 'D') {
            for (int i = 0; i < shipLength; i++) {
                if (board[row + i][col] != 'X') {
                    flag = 1;
                }
            }
            if(flag == 1) {
                printf("Invalid placement. Try again.\n");
                continue;
            }

            for (int i = 0; i < shipLength; i++) {
                board[row + i][col] = symbol;
            }
            (*shipLengthsCounter) += shipLength;
        } else if (direction == 'A') {
            for (int i = 0; i < shipLength; i++) {
                if (board[row - i][col] != 'X') {
                    flag = 1;
                }
            }
            if(flag == 1) {
                printf("Invalid placement. Try again.\n");
                continue;
            }

            for (int i = 0; i < shipLength; i++) {
                board[row - i][col] = symbol;
            }
            (*shipLengthsCounter) += shipLength;
        } else {
            printf("Invalid direction. Try again.\n");
            continue;
        }


        break;

    } while (1);
}


void attack(char board[*r][*c], char opponentBoard[*r][*c], int* hitCounter , int* attackCounter, int* shipLengthsCounter) {
    int row, col;

    printf("Valid attacks in the game (Valid Attack Counter) : %d", *attackCounter);
    printf("\n");
    printf("Your success attacks (Hit Counter) : %d", *hitCounter);
    printf("\nEnter your attack (row, col): ");
    scanf("%d %d", &row, &col);


    if (opponentBoard[row][col] != 'X') {
        printf("You've already attacked this position. Try again.\n");
        attack(board, opponentBoard, hitCounter, attackCounter, shipLengthsCounter);
        return;
    }


    switch (board[row][col]) {
        case 'X':
            opponentBoard[row][col] = 'M';
            (*attackCounter)++;
            printf("Miss!\n");
            break;
        case 'A':
        case 'D':
        case 'B':
            opponentBoard[row][col] = 'H';
            printf("Hit!\n");
            (*attackCounter)++;
            (*hitCounter)++;
            if (*hitCounter == *shipLengthsCounter) {return;} // will change if any ships added
            attack(board,opponentBoard,hitCounter, attackCounter, shipLengthsCounter);
            break;
    }
}

int main() {

    displayTheWelcomeScreen();

    int ROW , COLUMN;
    printf("Oyun alanı için ROW ve COLUMN belirleyiniz: ");
    scanf("%d%d",&ROW,&COLUMN);

    r = &ROW;
    c = &COLUMN;

    char player1Board[ROW][COLUMN], player1AttackBoard[ROW][COLUMN];
    char player2Board[ROW][COLUMN], player2AttackBoard[ROW][COLUMN];

    // Initialize boards
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            player1Board[i][j] = 'X';
            player1AttackBoard[i][j] = 'X';
            player2Board[i][j] = 'X';
            player2AttackBoard[i][j] = 'X';
        }
    }

    int shipLengthsCounter = 0;

    printf("Player1 your turn to place ships \n");

    placeShip(player1Board, 3, 'A', &shipLengthsCounter);
    placeShip(player1Board, 2, 'D', &shipLengthsCounter);
    placeShip(player1Board, 2, 'D', &shipLengthsCounter);
    placeShip(player1Board, 2, 'D', &shipLengthsCounter);
    placeShip(player1Board, 1, 'B', &shipLengthsCounter);
    placeShip(player1Board, 1, 'B', &shipLengthsCounter);
    placeShip(player1Board, 1, 'B', &shipLengthsCounter);
    placeShip(player1Board, 1, 'B', &shipLengthsCounter);

    printf("Player2 your turn to place ships \n");

    placeShip(player2Board, 3, 'A', &shipLengthsCounter);
    placeShip(player2Board, 2, 'D', &shipLengthsCounter);
    placeShip(player2Board, 2, 'D', &shipLengthsCounter);
    placeShip(player2Board, 2, 'D', &shipLengthsCounter);
    placeShip(player2Board, 1, 'B', &shipLengthsCounter);
    placeShip(player2Board, 1, 'B', &shipLengthsCounter);
    placeShip(player2Board, 1, 'B', &shipLengthsCounter);
    placeShip(player2Board, 1, 'B', &shipLengthsCounter);

    shipLengthsCounter /= 2;

    int counter = 0;
    int player1HitCounter = 0;
    int player2HitCounter = 0;


    while (1) {

        printf("\nPlayer 1's turn:\n");
        printBoard(player1AttackBoard);
        attack(player2Board, player1AttackBoard, &player1HitCounter, &counter, &shipLengthsCounter);
        system("cls");

        if (player1HitCounter == shipLengthsCounter) { // will change if any ships added
            printf("\n----- Player1 Wins! -----\n");
            printBoard(player1AttackBoard);
            break;
        }

        printf("\nPlayer 2's turn:\n");
        printBoard(player2AttackBoard);
        attack(player1Board, player2AttackBoard, &player2HitCounter, &counter, &shipLengthsCounter);
        system("cls");

        if (player2HitCounter == shipLengthsCounter) { // will change if any ships added
            printf("\n----- Player2 Wins! -----\n");
            printBoard(player2AttackBoard);
            break;
        }
    }

    return 0;
}
