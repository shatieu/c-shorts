#include <stdio.h>


/*
 *
 *             BASIC SETTING
 * each player 2 cards river 5 cards tern 4 cards
 * card 2,3...T,J,Q,K,A + h,d,s,c e.g. (Ah - ace of hearts)
 * but inside are cards kept as 2,3,..A,B,C,D,E for better comparing possibilities
 *
 *
 * inputs not checked, cards splitted by space players by \n
 *
 * Mode without param
 * determins winning player
 * runs and asks until EOF on stdin
 *
 *
 */
//-----------------------------------------------------------------------------------
// in game mechanics e.g. search high card etc.
//-----------------------------------------------------------------------------------
/**
 * finds highest card of given player
 * @param player
 * @param river
 * @param result
 * @return card
 */
/*
const char* highCard(char* player, char* river, char* result){
    char maxx = 0;
    char maxxcolour;
    if (player[0] > player[2]){
        maxx = player[0];
        maxxcolour = player[1];
    } else{
        maxx = player[2];
        maxxcolour = player[3];
    }
    for(int i = 0; i < 5; i++){
        if (river[i*2] > maxx){
            maxx = river[i*2];
            maxxcolour = player[2*i+1];
        }
    }
    result[0] = maxx;
    result[1] = maxxcolour;
    result[2] = '\0';
    return result;
}
 */
/**
 * compares highcards of two players
 * @param playerOne
 * @param playerTwo
 * @param river
 * @return
 */
/*
int compareHighcards(char* playerOne, char* playerTwo, char* river){
    char highSt [3];
    char highNd [3];
    highCard(playerOne,river, highSt);
    highCard(playerTwo,river, highNd);
    if(highSt[0] == highNd[0]){
        return 0;
    }
    if(highSt[0] > highNd[0]){
        return 1;
    }
    return 2;
}
*/
int isStraight(char seven [7][2]){
    int array[15];
    for(int i = 0;i<15; i++){
        array[i] = 0;
    }
    for(int i = 0;i<7; i++){
        if(seven[i][0] == 'e'){
            array[1] = 1;
            array[14] = 1;
            continue;
        }
        if(seven[i][0]<65){
            array[seven[i][0]-48] = 1;
            continue;
        }
        array[seven[i][0]-87] = 1;
    }
    int maxLength = 1;
    int maxValue = 0;
    int length = 1;
    for(int i = 0;i<14; i++){
        if(array[i] && array[i+1]){
            length++;
            if(length>maxLength){
                maxLength = length;
            }
            if(length >= 5){
                maxValue = i+1;
            }
        } else{
            length = 1;
        }

    }
    if(maxLength >= 5){
        if(maxValue < 10){
            return maxValue+48;
        } else{
            return maxValue+87;
        }
    } else{
        return 0;
    }

}

/**
 *
 * @param seven
 * @return 0 when there is not flush,
 * 'h'  for hearts flush
 * 'd' diamonds
 * 'c' cross
 * 's' spades
 */
int isFlush(char seven[7][2]){
    int hCount = 0;
    int cCount = 0;
    int dCount = 0;
    int sCount = 0;
    for(int i = 0; i < 7; i++){
        switch (seven[i][1]){
            case 'h':
                hCount++;
                break;
            case 'c':
                cCount++;
                break;
            case 'd':
                dCount++;
                break;
            default:
                sCount++;
        }
    }
    if(hCount >= 5){
        return 'h';
    }
    if( dCount >= 5){
        return 'd';
    }
    if( cCount >= 5){
        return 'c';
    }
    if( sCount >= 5){
        return 's';
    }else{
        return 0;
    }
}
void cardRepetitions(char seven [7][2], int cardxTimes [7][2]){
    int taken = 0;
    for(int i = 0; i < 7; i++) {
        cardxTimes[i][0] = 0;
        cardxTimes[i][1] = 0;
    }
    for(int i = 0; i < 7; i++){

        for(int j= 0; j<7; j++){
            if(cardxTimes[j][0] == seven[i][0]){
                cardxTimes[j][1]++;
                break;
            }
            if(j > taken){
                cardxTimes[taken][0] = seven[i][0];
                cardxTimes[taken][1] = 1;
                taken++;
                break;

            }

        }
    }
}

/**
 * return 2 for one pair
 * 30 for trips
 * 50 for fullhouse
 * 22 for two pairs
 * 400 for poker
 * 0 for no repeating cards
 *
 * @param seven
 * @return see above
 */
int decideCardRepetitions (int cardxTimes [7][2]){

    int sumOfRepeatingCards = 0;
    int maxx = 1;
    for(int i = 0; i < 7; i++){
        if(cardxTimes[i][1]>1){
            if(cardxTimes[i][1] > maxx){
                maxx = cardxTimes[i][1];
            }
            sumOfRepeatingCards += cardxTimes[i][1];
        }
    }

    if(maxx == 4){
        return 400;
    }
    if((sumOfRepeatingCards >= 5) && maxx == 3){
        return 50;
    }
    if(sumOfRepeatingCards == 4 || sumOfRepeatingCards == 6){
        return 22;
    }if(sumOfRepeatingCards == 3){
        return 30;
    }else{
        return sumOfRepeatingCards;
    }
}



// -----------------------------------------------------------------------------------
// read print and other functional things
//------------------------------------------------------------------------------------
/**
 * takes player and river and puts them into seven in asc order
 *
 * @param player
 * @param river
 * @param seven
 */
void makeOrderedSeven (char* player, char* river, char seven [7][2]){
    //both player cards

    for(int i = 0; i<7; i++){
        seven[i][0] = 0;
        //meanwhile useless step
        seven[i][1] = 0;
    }
    if(player[0]<player[2]) {
        seven[0][0] = player[0];
        seven[0][1] = player[1];
        seven[1][0] = player[2];
        seven[1][1] = player[3];
    }else{
        seven[0][0] = player[2];
        seven[0][1] = player[3];
        seven[1][0] = player[0];
        seven[1][1] = player[1];
    }
    int cardNum = 2;
    for(int i = 0; i < 5; i++){
        char card[2];
        card[0] = river[i*2];
        card[1] = river[i*2 +1];
        int nd = 0;
        while(seven[nd][0] < card[0] && nd < cardNum){
            nd++;
        }
        for(int p = 0; p < 6-nd; p++){
            seven[6-p][0] = seven[6-p-1][0];
            seven[6-p][1] = seven[6-p-1][1];
        }
        seven[nd][0] = card[0];
        seven[nd][1] = card[1];
        cardNum++;
    }
}
/**
 *
 * @param firstSeven
 * @param secondSeven
 * @param flushColor
 * @return in respect of winnig side
 */
int compareFlush(char firstSeven[7][2],char secondSeven[7][2], int flushColor){
    int firstInFlush[7];
    int secondInFlush[7];

    for(int i = 0; i <7; i++){
        firstInFlush[i] = 0;
        secondInFlush[i] = 0;
    }
    int taken = 0;
    for(int i = 0; i <7; i++){
        if(firstSeven[i][1] == flushColor){
            firstInFlush[taken] = firstSeven[i][0];
            taken++;
        }
    }
    taken = 0;
    for(int i = 0; i <7; i++){
        if(secondSeven[i][1] == flushColor){
            secondInFlush[taken] = secondSeven[i][0];
            taken++;
        }
    }
    for(int i = 0; i <7; i++){

    }
    int st = 6;
    int nd = 6;
    for(int i = 0; i <7; i++){
        if(firstInFlush[st] == 0){
            st--;
        }
        if(secondInFlush[nd] == 0){
            nd--;
        }
    }
    int count = 0;
    for(int i = 0; i < 7; i++){
        if(firstInFlush[st] > secondInFlush[nd]){
            return 1;
        }
        if(firstInFlush[st] < secondInFlush[nd]){
            return 2;
        }
        st--;
        nd--;
        count++;
        if(count == 5){
            break;
        }
    }
    return 0;
}


/**
 * CALL ONLY ON SEVENS WHICH HAVE STRAIGHT
 * @param firstSeven
 * @param highestCardInStraight
 * @return 1 when straight flush 0 else
 */
int isStraightFlush(char firstSeven[7][2], int highestCardInStraight) {
    int array[15];
    int flushColor = isFlush(firstSeven);
    for (int i = 0; i < 15; i++) {
        array[i] = 0;
    }
    for (int i = 0; i < 7; i++) {
        if (firstSeven[i][0] == 'e') {
            if (firstSeven[i][1] == flushColor) {
                array[1] = 1;
                array[14] = 1;
            }
            continue;
        }
        if (firstSeven[i][0] < 65) {
            if (firstSeven[i][1] == flushColor) {
                array[firstSeven[i][0] - 48] = 1;
            }
            continue;
        }
        if (firstSeven[i][1] == flushColor) {
            array[firstSeven[i][0] - 87] = 1;
        }
    }
    int maxLength = 1;
    int length = 1;
    for(int i = 0;i<14; i++){
        if(array[i] && array[i+1]){
            length++;
            if(length>maxLength){
                maxLength = length;
            }
        } else{
            length = 1;
        }

    }
    if(maxLength >= 5){
        return 1;
    } else{
        return 0;
        if(highestCardInStraight){
            array[0]=1;
        }
    }
}
/*
int isStraightFlush(char firstSeven[7][2], int highestCardInStraight){
    int flushColor = isFlush(firstSeven);
    int count = 0;
    int lastInFlush = 0;
    for(int i = 6; i >= 0 ; i--){
        if(firstSeven[i][0] == highestCardInStraight && firstSeven[i][1] == flushColor) {
            count++;
            lastInFlush = firstSeven[i][0];
            for (int y =i-1; y >= 0; y--) {
                if (firstSeven[y][0] - lastInFlush == -1 || firstSeven[y][0] - lastInFlush == - 40 ){
                    if(firstSeven[y][1] == flushColor){
                        lastInFlush = firstSeven[y][0];
                        count++;
                    }
                }
            }
        }
    }
    return count >= 5;
}
 */
int compareFullHouse (int cardRepFirst [7][2], int cardRepSecond [7][2]){
    int threeFirst = 0;
    int threeSecond = 0;
    int twoFirst = 0;
    int twoSecond = 0;
    for (int i = 0; i < 7; i++) {
        if (cardRepFirst[i][1] == 3 && cardRepFirst[i][0] > threeFirst){
            threeFirst = cardRepFirst[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (cardRepSecond[i][1] == 3 && cardRepSecond[i][0] > threeSecond){
            threeSecond = cardRepSecond[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (cardRepFirst[i][1] == 2 && cardRepFirst[i][0] > twoFirst && threeFirst != cardRepFirst[i][0]){
            twoFirst = cardRepFirst[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (cardRepSecond[i][1] == 2 && cardRepSecond[i][0] > twoSecond && threeSecond != cardRepSecond[i][0]){
            twoSecond = cardRepSecond[i][0];
        }
    }
    if(threeFirst == threeSecond){
        if(twoFirst == twoSecond){
            return 0;
        }
        if(twoFirst > twoSecond){
            return 1;
        }else{
            return 2;
        }
    }
    if(threeFirst > threeSecond){
        return 1;
    } else{
        return 2;
    }


}
int compareTwoPairs(int cardRepFirst [7][2], int cardRepSecond [7][2]){
    int twohighFirst = 0;
    int twohighSecond = 0;
    int twoFirst = 0;
    int twoSecond = 0;
    int highfirst = 0;
    int highsecond = 0;

    for (int i = 0; i < 7; i++) {
        if (cardRepFirst[i][1] == 2 && cardRepFirst[i][0] > twohighFirst){
            twohighFirst = cardRepFirst[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (cardRepSecond[i][1] == 2 && cardRepSecond[i][0] > twohighSecond){
            twohighSecond = cardRepSecond[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (cardRepFirst[i][1] == 2 && twohighFirst != cardRepFirst[i][0]){
            twoFirst = cardRepFirst[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (cardRepSecond[i][1] == 2 && twohighSecond != cardRepSecond[i][0]){
            twoSecond = cardRepSecond[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if(highfirst < cardRepFirst[i][0] && cardRepFirst[i][0] != twoFirst && cardRepFirst[i][0] != twohighFirst){
            highfirst = cardRepFirst[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if(cardRepSecond[i][0] > highsecond && cardRepSecond[i][0] != twoSecond && cardRepSecond[i][0] != twohighSecond){
            highsecond = cardRepSecond[i][0];
        }
    }
    if(twohighFirst == twohighSecond){
        if(twoFirst == twoSecond){
            if(highfirst > highsecond){
                return 1;
            }
            if(highsecond > highfirst){
                return 2;
            } else{
                return 0;
            }

        }
        if(twoFirst > twoSecond){
            return 1;
        }else{
            return 2;
        }
    } else{
        if(twohighFirst > twohighSecond){
            return 1;
        }else {
            return 2;
        }
    }

}
int compareTrips(int cardRepFirst[7][2], int cardRepSecond[7][2]){
    int tripsFirst = 0;
    int tripsSecond = 0;
    int ndHighFirst = 0;
    int ndHighSecond = 0;
    int highfirst = 0;
    int highsecond = 0;

    for (int i = 0; i < 7; i++) {
        if (cardRepFirst[i][1] == 3){
            tripsFirst = cardRepFirst[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (cardRepSecond[i][1] == 3){
            tripsSecond = cardRepSecond[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if(highfirst < cardRepFirst[i][0] && cardRepFirst[i][0] != tripsFirst){
            highfirst = cardRepFirst[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if(cardRepSecond[i][0] > highsecond && cardRepSecond[i][0] != tripsSecond){
            highsecond = cardRepSecond[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (cardRepFirst[i][0] > ndHighFirst && tripsFirst != cardRepFirst[i][0] && cardRepFirst[i][0] != highfirst){
            ndHighFirst = cardRepFirst[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (cardRepSecond[i][0] > ndHighSecond && tripsSecond != cardRepSecond[i][0] && cardRepSecond[i][0] != highsecond){
            ndHighSecond = cardRepSecond[i][0];
        }
    }
    if(tripsFirst == tripsSecond){
        if(highfirst == highsecond){
            if(ndHighFirst == ndHighSecond){
                return 0;
            }
            if(ndHighFirst > ndHighSecond){
                return 1;
            }
            return 2;
        }
        if(highfirst >highsecond){
            return 1;
        }
        return 2;
    }
    if (tripsFirst >tripsSecond){
        return 1;
    }
    if(tripsFirst < tripsSecond){
        return 2;
    }
    return 0;
}
int comparePoker(int cardRepFirst[7][2], int cardRepSecond[7][2]){
    int pokerFirst = 0;
    int pokerSecond = 0;
    int highfirst = 0;
    int highsecond = 0;
    for (int i = 0; i < 7; i++) {
        if (cardRepFirst[i][1] == 4){
            pokerFirst = cardRepFirst[i][0];
        }
        if (cardRepSecond[i][1] == 4){
            pokerSecond = cardRepSecond[i][0];
        }
    }
    for (int i = 0; i < 7; i++) {
        if(highfirst < cardRepFirst[i][0] && cardRepFirst[i][0] != pokerFirst){
            highfirst = cardRepFirst[i][0];
        }

        if(cardRepSecond[i][0] > highsecond && cardRepSecond[i][0] != pokerSecond){
            highsecond = cardRepSecond[i][0];
        }

    }
    if(pokerFirst == pokerSecond){
        if(highfirst == highsecond){
            return 0;
        }
        if(highfirst > highsecond){
            return 1;
        }
        return 2;
    }
    if(pokerFirst > pokerSecond){
        return 1;
    }
    return 2;
}
int comparePair(int cardRepFirst[7][2], int cardRepSecond[7][2]){
    int firstPair = 0;
    int secodnPair = 0;
    for (int i = 0; i < 7; i++) {
        if (cardRepFirst[i][1] == 2){
            firstPair = cardRepFirst[i][0];

        }
        if (cardRepSecond[i][1] == 2){
            secodnPair = cardRepSecond[i][0];

        }
    }
    int pairWasAccounted = 0;
    if(firstPair == secodnPair){
        for (int i = 5; i > 2; i--) {

            if(cardRepFirst[i][0] > cardRepSecond[i][0]){
                return 1;
            }
            if(cardRepSecond[i][0] > cardRepFirst[i][0]){
                return 2;
            }
            if(cardRepFirst[i][0] == firstPair){
                pairWasAccounted = 1;
            }
        }
        if(pairWasAccounted){
            if(cardRepFirst[2][0] > cardRepSecond[2][0]){
                return 1;
            }
            if(cardRepFirst[2][0] < cardRepSecond[2][0]){
                return 2;
            }
        }
        return 0;
    }
    if (firstPair > secodnPair){
        return 1;
    }
    return 2;


}
int highCardCorrectly(char firstSeven[7][2], char secondSeven[7][2]){
    for(int i = 6; i >=2; i--){
        if(firstSeven[i][0]>secondSeven[i][0]){
            return 1;
        }
        if(firstSeven[i][0] < secondSeven[i][0]){
            return 2;
        }
    }
    return 0;
}
int compareSameCards(char firstSeven[7][2], char secondSeven[7][2]) {
    int cardxTimesFirst[7][2];
    int cardxTimesSecond[7][2];
    cardRepetitions(firstSeven,cardxTimesFirst);
    cardRepetitions(secondSeven, cardxTimesSecond);

    //these tell what kind of repetition it is fullhouse poker etc... Do not touch
    const int stWhatRepetition = decideCardRepetitions(cardxTimesFirst);
    const int ndWhatRepetition = decideCardRepetitions(cardxTimesSecond);


    if(stWhatRepetition == ndWhatRepetition) {

        switch (stWhatRepetition) {
            //poker
            case 400:
                return comparePoker(cardxTimesFirst,cardxTimesSecond)+400;
            // fullhouse
            case 50 :
                return compareFullHouse(cardxTimesFirst,cardxTimesSecond)+50;
            //trips
            case 22:
                return compareTwoPairs(cardxTimesFirst,cardxTimesSecond);
            case 30:
                return compareTrips(cardxTimesFirst,cardxTimesSecond);
            case 2:
                return comparePair(cardxTimesFirst, cardxTimesSecond);
            default:
                return highCardCorrectly(firstSeven,secondSeven);


        }
    }else{
        if(stWhatRepetition > ndWhatRepetition){
            if(stWhatRepetition >= 50){
                return 1+ stWhatRepetition;
            }
            return 1;
        }
        //else will suffice like this...
        if(stWhatRepetition < ndWhatRepetition){
            if(ndWhatRepetition >= 50){
                return ndWhatRepetition+2;
            }
            return 2;
        }
        return 0;
    }

}



int evaluate(char* first, char* second, char* river){
    char firstSeven [7][2];
    char secondSeven [7][2];
    makeOrderedSeven(first,river,firstSeven);
    makeOrderedSeven(second, river, secondSeven);
    int resultFirst = isStraight(firstSeven);
    int resultSecond = isStraight(secondSeven);
    int tmpfirst = 0;
    int tmpsecond = 0;
    int whichStraightisHigher =0;
    int firstFlush = 0;
    int secondFlush = 0;
    //both straights
    tmpfirst = isStraightFlush(firstSeven,resultFirst);
    tmpsecond = isStraightFlush(secondSeven,resultSecond);
    if(resultFirst && resultSecond){

        //both straight flushes
        if(tmpfirst && tmpsecond){
            if(resultFirst == resultSecond){
                return 0;
            }
            if(resultFirst > resultSecond){
                return 1;
            }
            return 2;
        }

        if(resultFirst > resultSecond){
            whichStraightisHigher = 1;
        }
        if(resultSecond > resultFirst){
            whichStraightisHigher = 2;
        }
        if(resultFirst== resultSecond){
            whichStraightisHigher = 0;
        }
    }
    if(tmpfirst){
        return 1;
    }
    if(tmpsecond){
        return 2;
    }
    // to be continued under comparing of same cards
    int comparisonOfSameCards = compareSameCards(firstSeven,secondSeven);
    if(comparisonOfSameCards >= 50){
        if(comparisonOfSameCards >= 400 ){
            return comparisonOfSameCards - 400;
        }else{
            return comparisonOfSameCards-50;
        }
    }
    //flushes
    firstFlush = isFlush(firstSeven);
    secondFlush = isFlush(secondSeven);
    if(secondFlush && firstFlush){
        return compareFlush(firstSeven,secondSeven,firstFlush);
    }
    if(firstFlush){
        return 1;
    }
    if (secondFlush){
        return 2;
    }
    //continuing straight
    if(resultFirst && resultSecond){
        return whichStraightisHigher;
    }
    if(resultFirst){
        return 1;
    }
    if(resultSecond){
        return 2;
    }
    //continuing card repetition
    return comparisonOfSameCards;





}


/**
 * Reads from string and saves in different format for further usage to save
 * @param string
 * @param save
 */
void cardsFromString(const char *string, char *save) {
    int i = 0;
    int cardNum = 0;
    while (string[i] != '\0') {
        switch (string[i]){
            case ' ':
                i++;
                continue;

            case 'T':
                save[cardNum] = 'a';
                i++;
                cardNum++;
                break;
            case 'J':
                save[cardNum] = 'b';
                i++;
                cardNum++;
                break;
            case 'Q':
                save[cardNum] = 'c';
                i++;
                cardNum++;
                break;
            case 'K':
                save[cardNum] = 'd';
                i++;
                cardNum++;
                break;
            case 'A':
                save[cardNum] = 'e';
                i++;
                cardNum++;
                break;
            default:
                save[cardNum] = string[i];
                i++;
                cardNum++;

        }
    }
    save[cardNum] = '\0';
}


/**
 * reads stdin !caution works just for correct input (less than 16 chars)
 * @param save
 * @return 0 when EOF else 1
 */
int readString (char* save){
    char c = (char)getchar();
    if(c == EOF){
        return 0;
    }
    int i =0;
    while(c != '\n'){
        save[i] = c;
        c = (char)getchar();
        i++;
    }
    save[i] = '\0';
    return 1;
}

/**
 * prints W-in D-raw L-ost from POV of first player based on result (0 - D ,1 - W,2 - L)
 * @param result
 */
void printResult(int result){
    char c;
    switch (result) {
        case 0 :
            c = 'D';
            break;
        case 1 :
            c = 'W';
            break;
        default:
            c = 'L';
    }
    printf("%c", c);
    printf("\n");
}

void createAllCards(int save [52][2]){
    char colors [] = {'h','d','s','c'};
    for(int i = 0; i < 13; i++){
        for(int j= 0; j<4; j++){
            if(i<8){
                save[i*4+j][0] = '2'+i;
                save[i*4+j][1] = colors[j];
            } else{
                save[i*4 + j ][0] = 'a'+ i -8;
                save[i*4 + j ][1] = colors[j];
            }
        }
    }
}
int changeLetter(int i){
    if(i >= 'a'){
        switch(i){
            case 'a':
                return 'T';
            case 'b':
                return 'J';
            case 'c':
                return 'Q';
            case 'd':
                return 'K';
            default:
                return 'A';
        }
    }
    return i;
}
int isThereSame(char first [5], char river[11], char second[5], int wantsToAdd [2]){
    int i =0;
    int flag = 0;
    while(first[i] != '\0'){
        if(wantsToAdd[0] == first[i] && i%2 == 0){
            if(wantsToAdd[1] == first[i + 1]){
                flag = 1;
            }
        }
        i++;
    }
    i=0;
    while(river[i] != '\0'){
        if(wantsToAdd[0] == river[i] && i%2 == 0){
            if(wantsToAdd[1] == river[i + 1]){
                flag = 1;
            }
        }
        i++;
    }
    if(wantsToAdd[0] == second[0]){
        if(wantsToAdd[1] == second[1]){
            flag = 1;
        }
    }
    return flag;
}

int main(int argc, char *argv[])
{
    /**************************************************/
    /* ------------- IMPORTANT NOTICE --------------- */
    /* Before submitting your homework, make sure you */
    /* REMOVE the following two lines with UNUSED:    */
    /**************************************************/
    char first [5];
    char second [5];
    char river [11];
    char string [17];
    int result = 0;
    // who won
    if(argc == 1){

        while(readString(string) == 1) {

            cardsFromString(string, first);
            readString(string);
            cardsFromString(string, second);
            readString(string);
            cardsFromString(string, river);
            result = evaluate(first,second,river);
            printResult(result);
        }
        return 0;
    }
    // count best card
    int riverCardresult [52][3];
    int allCards [52][2];
    if (argc > 1){
        createAllCards(allCards);
        while(readString(string) == 1) {
            cardsFromString(string, first);
            readString(string);
            cardsFromString(string, river);
            int wantsToAdd[2];
            int total = 0;

            for (int i = 0; i < 52; i++) {
                second[0] = 0;
                second[1] = 0;
                riverCardresult[i][0] = allCards[i][0];
                riverCardresult[i][1] = allCards[i][1];
                riverCardresult[i][2] = 0;
                river[8] = '\0';
                wantsToAdd[0] = allCards[i][0];
                wantsToAdd[1] = allCards[i][1];
                if (isThereSame(first, river, second, wantsToAdd)) {
                    continue;
                }
                river[8] = (char) allCards[i][0];
                river[9] = (char) allCards[i][1];
                river[10] = '\0';
                for (int st = 0; st < 52; st++) {
                    wantsToAdd[0] = allCards[st][0];
                    wantsToAdd[1] = allCards[st][1];
                    if (isThereSame(first, river, second, wantsToAdd)) {
                        continue;
                    }
                    second[0] = (char) allCards[st][0];
                    second[1] = (char) allCards[st][1];
                    for (int nd = 0; nd < 52; nd++) {
                        wantsToAdd[0] = allCards[nd][0];
                        wantsToAdd[1] = allCards[nd][1];
                        if (isThereSame(first, river, second, wantsToAdd)) {
                            continue;
                        }
                        second[2] = (char) allCards[nd][0];
                        second[3] = (char) allCards[nd][1];
                        second[4] = '\0';
                        int res = evaluate(first, second, river);
                        if (res == 1) {
                            riverCardresult[i][2] += 2;
                        }
                        if (res == 0) {
                            riverCardresult[i][2]++;
                        }
                        if(res == 2){
                            total++;
                            total--;
                        }
                        total++;
                    }
                }
            }
            int goodCards[52][3];
            int maxx = 0;
            int taken = 0;
            for (int i = 0; i < 52; i++) {
                //riverCardresult[i][2] = (riverCardresult[i][2]/2) /total;
                if (riverCardresult[i][2] > maxx) {
                    maxx = riverCardresult[i][2];
                }
            }
            for (int i = 0; i < 52; i++) {
                if (riverCardresult[i][2] == maxx) {
                    goodCards[taken][0] = riverCardresult[i][0];
                    goodCards[taken][1] = riverCardresult[i][1];
                    goodCards[taken][2] = riverCardresult[i][2];
                    taken++;
                }
            }

            for (int i = 0; i < taken; i++) {
                putchar(changeLetter(goodCards[i][0]));
                putchar(goodCards[i][1]);
                if(i+1 < taken) {
                    putchar(' ');
                }
            }
            putchar('\n');
            if(argv[1][2] != 0) {
                int precision = argv[1][2] - 48;
                double toPrintRes = maxx;
                toPrintRes /= 4.0;
                toPrintRes /= 990.0;
                if (precision) {
                    printf("%.*lf\n", precision, toPrintRes);
                }
            }
        }

    }


    return 0;
}

//"Ad Ks" "9h 9s" "2h 3s 4d 5h 6s"