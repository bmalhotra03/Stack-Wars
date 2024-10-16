// Brij Malhotra
// lab9.cpp
// Purpose: Create a card game using stacks

#include <iostream>

using namespace std;

// Class declaration and function implementation

class StackWars {
    
    private:
        struct Node {
            int value;
            Node * next;
        };
        Node * top;

    public: 
        StackWars(){
            top = nullptr;
        }

        ~StackWars(){
            Node * nodePtr = nullptr;
            Node * nextNode = nullptr;

            nodePtr = top;

            while (nodePtr != nullptr){
                nextNode = nodePtr->next;
                delete nodePtr;
                nodePtr = nextNode;
            }
        }

        void push(int num){
            Node * newNode = nullptr;
            newNode = new Node();
            newNode->value = num;

            if (isEmpty()){
                top = newNode;
            } else {
                newNode->next = top;
                top = newNode;
            }
        }

        int pop(){
            int num;
            Node * temp = nullptr;

            if (isEmpty()){
                cout << "The stack is empty.\n";
            } else {
                num = top->value;
                temp = top->next;
                delete top;
                top = temp;
            }

            return num;
        }

        bool isEmpty(){
            bool status;

            if (!top){
                status = true;
            } else {
                status = false;
            }

            return status;
        }
};

// Deck generation and round functions 

void deckGen(StackWars &P1Deck, StackWars &P2Deck){

    for (int i = 0; i < 32; i++){       // rand() to generate random integers
        int num = rand() %  24 + 1;
        P1Deck.push(num);
    }

    for (int i = 0; i < 32; i++){
        int num = rand() % 24 + 1;
        P2Deck.push(num);
    }
}

void playRound(StackWars &P1Deck, StackWars &P1Discard, StackWars &P2Deck, StackWars &P2Discard){
    

    while (!P1Deck.isEmpty() && !P2Deck.isEmpty()){
        
        int num1 = P1Deck.pop();        // Popping from the stack and comparing the values and pushing accordingly
        int num2 = P2Deck.pop();

        if (num1 > num2){
            P1Discard.push(num1);
            P1Discard.push(num2);
        }

        if (num2 > num1){
            P2Discard.push(num1);
            P2Discard.push(num2);
        }

        cout << "Player 1's card was " << num1 << "." << endl;
        cout << "Player 2's card was " << num2 << "." << endl;
    }
}

void instructions(){
    cout << endl;
    cout << "Welcome to StackWars! Each player will have 2 stacks of cards, their main deck and a discard pile." << endl;
    cout << "The decks are randomly generated here. This game will be played in a comparison method of the cards." << endl;
    cout << "If Player1's card is greater than Player2's card, both cards will be added to Player1's discard stack." << endl;
    cout << "After each round, players will swap their main deck and discard stack and then play another round :D" << endl;
    cout << "The game will continue for 100 rounds or up until one of the player's card stacks are empty! Enjoy :D" << endl << endl; 
}

int main(){
    
    StackWars * P1Deck = new StackWars();   // All the stack objects are pointers so that I can use the swap function
    StackWars * P2Deck = new StackWars();
    StackWars * P1Discard = new StackWars();
    StackWars * P2Discard = new StackWars();

    instructions();

    deckGen(*P1Deck, *P2Deck);

    for (int i = 0; i < 100 && (!P1Deck->isEmpty() && !P2Deck->isEmpty()); i++){  // Conditions for 100 iterations or stacks being empty 
        playRound(*P1Deck, *P1Discard, *P2Deck, *P2Discard);
        swap(P1Deck, P1Discard);
        swap(P2Deck, P2Discard);
    }

    cout << endl;

    if (P1Deck->isEmpty() || P1Discard->isEmpty()){       
        cout << "Player 1 has an empty stack of cards. ∴ Player 2 has won the game!" << endl;   // Conditions of game conclusion
    } else if (P2Deck->isEmpty() || P2Discard->isEmpty()){
        cout << "Player 2 has an empty stack of cards. ∴ Player 1 has won the game!" << endl;
    } else {
        cout << "No card decks are empty after 100 rounds. Game has ended in a draw." << endl;
    }
    
    cout << endl;

    delete P1Deck;      // Deallocating heap data
    delete P2Deck;
    delete P1Discard;
    delete P2Discard;

    return 0;
}