#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;
const string INVALID_CMD = "Comando inválido!";
const string HEART = "C";
const string CLUB = "P";
const string DIAMOND = "O";
const string SPADE = "E";

struct card {
    int value;
    string suit;
    bool is_turned;
	bool is_valid;
};

vector<card> deck;
stack<card> stock;
stack<card> discard;

stack<card> col1;
stack<card> col2;
stack<card> col3;
stack<card> col4;
stack<card> col5;
stack<card> col6;
stack<card> col7;

stack<card> fundation_heart;
stack<card> fundation_club;
stack<card> fundation_diamond;
stack<card> fundation_spade;

string toString(card element) {
		if (element.is_valid == false) {
			return "----";
		} else if (element.is_turned == true) {
			return "????";
		} else if(element.value < 10) {
			return "0" + to_string(element.value) + ":" + element.suit;
		} else {
			return to_string(element.value) + ":" + element.suit;
		}
}

void assign_cards(string suit) {
	card c;
	for (int i = 0; i < 13; i++)  {
		c.suit = suit;
		c.value = (i+1);
		c.is_turned = true;
		c.is_valid = true;
		deck.push_back(c);
	}		
}

void build_deck() {
	assign_cards(HEART); 
	assign_cards(CLUB);
	assign_cards(DIAMOND);
	assign_cards(SPADE);
}

void build_stock() {
	for (int i = 0; i < 24; i++) {
		stock.push(deck.data()[i]);
		deck.erase(deck.begin() + i);
	}	
}

void build_column(stack<card>* column, int quantity) {
	for(int i = 0; i < quantity; i++) {
		card c = deck.data()[i];
		if(i == quantity -1) {
			c.is_turned = false;
		}
		column->push(c);
		deck.erase(deck.begin() + i);
	}

	for(int i = 0; i < 13 - quantity; i++) {
		card c;
		c.is_valid = false;
		column->push(c);
	}
}

void build_columns() {
	build_column(&col1, 1);
	build_column(&col2, 2);
	build_column(&col3, 3);
	build_column(&col4, 4);
	build_column(&col5, 5);
	build_column(&col6, 6);
	build_column(&col7, 7);
}

void replace_stock() {
  for (int i = 0; i < discard.size(); i++) {
    card c = discard.top();
    discard.pop();
	c.is_turned = false;
    stock.push(c);
	
  }
}

bool acess_stock(bool flag) {
	card c;
	flag = false;
	if (!stock.empty()) {	
		c = stock.top();
		stock.pop();
		c.is_turned = false;	
		discard.push(c);		
	} else {
		flag = true;
		if (!discard.empty()) {
			replace_stock();
		}
  	}
	return flag;	
}

void discard_to_fundation_heart() {
	if (!discard.empty()) {
		card c = discard.top();
		if (fundation_heart.empty()) {
			fundation_heart.push(c);
			discard.pop();
		} else if (c.is_valid && 
						c.is_turned &&
						fundation_heart.top().value < c.value &&
						fundation_heart.top().suit.compare(c.suit)) {

			fundation_heart.push(c);
			discard.pop();
		}	
	}	
}

void discard_to_fundation_club() {
	if (!discard.empty()) {
		card c = discard.top();
		if (fundation_club.empty()) {
			fundation_club.push(c);
			discard.pop();
		} else if (c.is_valid && 
						c.is_turned &&
						fundation_club.top().value < c.value &&
						fundation_club.top().suit.compare(c.suit)) {

			fundation_club.push(c);
			discard.pop();
		}	
	}	
}

void discard_to_fundation_diamond() {
	if (!discard.empty()) {
		card c = discard.top();
		if (fundation_diamond.empty()) {
			fundation_diamond.push(c);
			discard.pop();
		} else if (c.is_valid && 
						c.is_turned &&
						fundation_diamond.top().value < c.value &&
						fundation_diamond.top().suit.compare(c.suit)) {

			fundation_diamond.push(c);
			discard.pop();
		}	
	}	
}

void discard_to_fundation_spade() {
	if (!discard.empty()) {
		card c = discard.top();
		if (fundation_spade.empty()) {
			fundation_spade.push(c);
			discard.pop();
		} else if (c.is_valid && 
						c.is_turned &&
						fundation_spade.top().value < c.value &&
						fundation_spade.top().suit.compare(c.suit)) {

			fundation_spade.push(c);
			discard.pop();
		}	
	}	
}

bool suits_compatibles(string suit1, string suit2) {
	bool flag = false;

	if (suit1.compare(HEART) || suit1.compare(DIAMOND) && ((suit2.compare(CLUB)) || suit2.compare(SPADE))) {
		flag = true;
	} else if ((suit1.compare(CLUB) || suit1.compare(SPADE)) && (suit2.compare(HEART) || suit2.compare(DIAMOND))) {
		flag = true;
	}

	return flag;
}

void discard_to_fundation() {
	cout << "Escolha uma opção de nipe da fundação." << endl << endl;
	cout << "(1) Copas" << endl;
	cout << "(2) Ouro" << endl;
	cout << "(3) Paus" << endl;
	cout << "(4) Espada" << endl;
	int option;
	cin >> option;

	if (option == 1) {
		discard_to_fundation_heart();
	} else if (option == 2) {
		discard_to_fundation_diamond();
	} else if (option == 3) {
		discard_to_fundation_club();
	} else if (option == 4) {
		discard_to_fundation_spade();
	} else {
		cout << endl << INVALID_CMD << endl;
	}
}

void discard_to_colunm(stack <card>* colunm) {
	if (!discard.empty()) {
		card c = discard.top();
		discard.pop();
		if (colunm->empty() && discard.top().value == 13) { // Se for um rei e a coluna tiver vazia, coloca			
			colunm->push(c);
		} else {
			stack<card> aux;
			card aux_card;
			while (!colunm->top().is_valid && !colunm->empty()) {    // Ando nos espaços vazios até chegar num lugar com carta 
				aux_card = colunm->top();
				aux.push(aux_card);
				colunm->pop();
			}
			
			if (c.value < aux_card.value && suits_compatibles(c.suit, aux_card.suit)) {
				colunm->push(c);

				while (colunm->size() <= 13 && !aux.empty()) {
					aux_card = aux.top();
					colunm->push(aux_card);
					aux.pop();
				}				 
			}
		}
	}
}

void discard_to_colunm_options() {
	cout << "Para qual das colunas você deseja mover?" << endl;
	cout << "1" << endl;
	cout << "2" << endl;
	cout << "3" << endl;
	cout << "4" << endl;
	cout << "5" << endl;
	cout << "6" << endl;
	cout << "7" << endl;	

	int option;
	if (option == 1) {	
		discard_to_colunm(&col1);
	} else if(option == 2) {
		discard_to_colunm(&col2);
	} else if (option == 3) {
		discard_to_colunm(&col3);
	} else if (option == 4) {
		discard_to_colunm(&col4);
	} else if (option == 5) {
		discard_to_colunm(&col5);
	} else if (option == 6) {
		discard_to_colunm(&col6);
	} else if (option == 7) {
		discard_to_colunm(&col7);
	} else {
		cout << endl << INVALID_CMD << endl;
	}

}

void column_to_fundation() {

}

void between_colunms() {

}

void fundation_to_colunms() {

}

void move_cards() {
		cout << "Escolha uma opcao de movimentacao:" << endl << endl;
		cout << "Opcao (1): mover do descarte para as fundacoes." << endl;
		cout << "Opcao (2): mover do descarte para coluna" << endl;
		cout << "Opcao (3): mover das colunas para as fundacoes." << endl;
		cout << "Opcao (4): mover entre colunas." << endl;
		cout << "Opcao (5): mover das fundacoes para colunas" << endl << endl;
		int option;
		
		cout << "Opcao: ";
		cin >>  option;
		cout << endl;
		
		if (option == 1) {
			discard_to_fundation();
		} else if(option == 2) {
			discard_to_colunm_options();
		} else if (option == 3) {
			column_to_fundation();
		} else if (option == 4) {
			between_colunms();
		} else if (option == 5) {
			fundation_to_colunms();
		} else {
			cout << endl << INVALID_CMD << endl;
		}		 
}

void actual_state() {
	stack<card> aux1;
	stack<card> aux2;
	stack<card> aux3;
	stack<card> aux4;
	stack<card> aux5;
	stack<card> aux6;
	stack<card> aux7;

	for(int i = 0; i < 13; i++) {
		card c1 = col1.top();
		card c2 = col2.top();
		card c3 = col3.top();
		card c4 = col4.top();
		card c5 = col5.top();
		card c6 = col6.top();
		card c7 = col7.top();
		col1.pop();
		col2.pop();
		col3.pop();
		col4.pop();
		col5.pop();
		col6.pop();
		col7.pop();
		aux1.push(c1);
		aux2.push(c2);
		aux3.push(c3);
		aux4.push(c4);
		aux5.push(c5);
		aux6.push(c6);
		aux7.push(c7);
	}

	for(int i = 0; i < 13; i++) {
		int j = i+1;
		string col;
		if(j < 10) {
			col = "0" + to_string(j);
		} else {
			col = to_string(j);
		}
		card c1 = aux1.top();
		card c2 = aux2.top();
		card c3 = aux3.top();
		card c4 = aux4.top();
		card c5 = aux5.top();
		card c6 = aux6.top();
		card c7 = aux7.top();
		cout << "--" + col +"--  ["+toString(c1)+"] ["+toString(c2)+"] ["+toString(c3)+"] ["+toString(c4)+"] ["+toString(c5)+"] ["+toString(c6)+"] ["+toString(c7)+"]" << endl;
		aux1.pop();
		aux2.pop();
		aux3.pop();
		aux4.pop();
		aux5.pop();
		aux6.pop();
		aux7.pop();
		col1.push(c1);
		col2.push(c2);
		col3.push(c3);
		col4.push(c4);
		col5.push(c5);
		col6.push(c6);
		col7.push(c7);
	}
}

void update_discard() {
	card c;
	if (!discard.empty()) {
		c = discard.top();		
		c.is_turned = false;		
	}
	cout << "------  ["+ toString(c) + "] <=> Descarte                       " << endl;
};

void legend() {
	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "/////////////////////// LEGENDA ///////////////////////////////////////////////////////////////////////" << endl;	
	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "/////// ??? : A carta está virada para baixo (Não é possível saber qual o seu valor ou nipe)." << endl;
	cout << "/////// --- : O campo da mesa está vazio, sendo possível mover uma carta para ele, caso obedeça as regras do jogo." << endl;
	cout << "/////// As cartas sempre vêm acompanhadas do seu valor (inteiro de 1 à 13, significando do Às ao Rei) e de seu nipe." << endl;
	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
};

void update_fundations() {
	card c, d, e, f;
	if (!fundation_heart.empty() && !fundation_club.empty() &&
		 !fundation_diamond.empty() && !fundation_spade.empty()) {
			 c = fundation_heart.top();
			 d = fundation_club.top();
			 e = fundation_diamond.top();
			 f = fundation_spade.top();			 			 
		 }
		 cout << "------  [" + toString(c) + "] ["+ toString(d) +"] ["+ toString(e) +"] ["+ toString(f) +"] <=> Fundacoes    " << endl << endl;
}

bool winner() {
	return fundation_club.empty() &&
	 	fundation_diamond.empty() &&
		  fundation_heart.empty() &&
		   fundation_spade.empty() &&
		   	stock.empty() && discard.empty();
}

void menu() {
	bool update_stock = false;
	while(true) {		
		cout << endl;	  		
		cout << "        --1-- --2-- --3-- --4-- --5-- --6-- --7--" << endl;
		if (update_stock) {
			cout << "------  [???] <=> ESTOQUE ATUALIZADO!            " << endl;
		} else {
			cout << "------  [???] <=> Estoque                        " << endl;
		}
		update_discard();
		cout << endl;
		actual_state();
		cout << endl;
		update_fundations();
		cout << "------   <C>    <P>    <O>    <E>" << endl;
		cout << "------   <O>    <A>    <U>    <S>" << endl;
		cout << "------   <P>    <U>    <R>    <P>" << endl;
		cout << "------   <A>    <S>    <O>    <A>" << endl;
		cout << "------   <S>    <->    <->    <D>" << endl;
		cout << "------   <->    <->    <->    <A>" << endl << endl;
		cout << "Escolha uma opcao:" << endl;
		cout << "Opcao (1): puxar uma carta do estoque." << endl;
		cout << "Opcao (2): mover uma carta." << endl;
		cout << "Opcao (3): legenda da simbologia do jogo." << endl;
		cout << "Opcao (4): sair do jogo." << endl << endl;
		int option;
		
		cout << "Opcao: ";
		cin >>  option;
		cout << endl;
		
		if (option == 1) {
			update_stock = acess_stock(update_stock);
		} else if(option == 2) {
			move_cards();
		} else if (option == 3) {
			legend();
		} else if ((option == 4) || winner()) {
			cout << endl << "Jogo encerrado." << endl << endl;
			cout << "     .-~~-." << endl;
			cout << "    {      }" << endl;
			cout << " .-~-.    .-~-." << endl;
			cout << "{              }" << endl;
			cout << " `.__.'||`.__.'" << endl;
			cout << "       ||" << endl;
			cout << "      '--`" << endl;
			break;
		} else {
			cout << endl << INVALID_CMD << endl << endl;
		}
	}
}

int main() {
	build_deck();
	random_shuffle(deck.begin(), deck.end());
	build_stock();    
	random_shuffle(deck.begin(), deck.end());
	build_columns();
	menu();		
	
	return 0;
}
