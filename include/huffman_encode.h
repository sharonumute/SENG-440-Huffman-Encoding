#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#define ALPHABET_SIZE 128
#define MAX_HUFFCODE_LEN  127

//Alphabet (encoded in ASCII)
const char ALPHABET[ALPHABET_SIZE] = {
    0,1,2,3,4,5,6,7,8,9,
    10,11,12,13,14,15,16,17,18,19,
    20,21,22,23,24,25,26,27,28,29,
    30,31,32,33,34,35,36,37,38,39,
    40,41,42,43,44,45,46,47,48,49,
    50,51,52,53,54,55,56,57,58,59,
    60,61,62,63,64,65,66,67,68,69,
    70,71,72,73,74,75,76,77,78,79,
    80,81,82,83,84,85,86,87,88,89,
    90,91,92,93,94,95,96,97,98,99,
    100,101,102,103,104,105,106,107,108,109,
    110,111,112,113,114,115,116,117,118,119,
    120,121,122,123,124,125,126,127
};

//Probabilities of the occurance of each value
const long double PROBABILITIES[ALPHABET_SIZE] = {
	0.5L,
	0.25L,
	0.125L,
	0.0625L,
	0.03125L,
	0.015625L,
	0.0078125L,
	0.00390625L,
	0.001953125L,
	0.0009765625L,
	0.00048828125L,
	0.000244140625L,
	0.0001220703125L,
	0.00006103515625L,
	0.000030517578125L,
	0.0000152587890625L,
	0.00000762939453125L,
	0.000003814697265625L,
	0.0000019073486328125L,
	0.00000095367431640625L,
	0.000000476837158203125L,
	0.0000002384185791015625L,
	0.00000011920928955078125L,
	0.000000059604644775390625L,
	0.0000000298023223876953125L,
	0.00000001490116119384765625L,
	0.000000007450580596923828125L,
	0.0000000037252902984619140625L,
	0.00000000186264514923095703125L,
	0.000000000931322574615478515625L,
	0.0000000004656612873077392578125L,
	0.00000000023283064365386962890625L,
	0.000000000116415321826934814453125L,
	0.0000000000582076609134674072265625L,
	0.00000000002910383045673370361328125L,
	0.000000000014551915228366851806640625L,
	0.0000000000072759576141834259033203125L,
	0.00000000000363797880709171295166015625L,
	0.000000000001818989403545856475830078125L,
	0.0000000000009094947017729282379150390625L,
	0.00000000000045474735088646411895751953125L,
	0.000000000000227373675443232059478759765625L,
	0.0000000000001136868377216160297393798828125L,
	0.00000000000005684341886080801486968994140625L,
	0.000000000000028421709430404007434844970703125L,
	0.0000000000000142108547152020037174224853515625L,
	0.00000000000000710542735760100185871124267578125L,
	0.000000000000003552713678800500929355621337890625L,
	0.0000000000000017763568394002504646778106689453125L,
	0.00000000000000088817841970012523233890533447265625L,
	0.000000000000000444089209850062616169452667236328125L,
	0.0000000000000002220446049250313080847263336181640625L,
	0.00000000000000011102230246251565404236316680908203125L,
	0.000000000000000055511151231257827021181583404541015625L,
	0.0000000000000000277555756156289135105907917022705078125L,
	0.00000000000000001387778780781445675529539585113525390625L,
	0.000000000000000006938893903907228377647697925567626953125L,
	0.0000000000000000034694469519536141888238489627838134765625L,
	0.00000000000000000173472347597680709441192448139190673828125L,
	0.000000000000000000867361737988403547205962240695953369140625L,
	0.0000000000000000004336808689942017736029811203479766845703125L,
	0.00000000000000000021684043449710088680149056017398834228515625L,
	0.000000000000000000108420217248550443400745280086994171142578125L,
	0.0000000000000000000542101086242752217003726400434970855712890625L,
	0.00000000000000000002710505431213761085018632002174854278564453125L,
	0.000000000000000000013552527156068805425093160010874271392822265625L,
	0.0000000000000000000067762635780344027125465800054371356964111328125L,
	0.00000000000000000000338813178901720135627329000271856784820556640625L,
	0.000000000000000000001694065894508600678136645001359283924102783203125L,
	0.0000000000000000000008470329472543003390683225006796419620513916015625L,
	0.00000000000000000000042351647362715016953416125033982098102569580078125L,
	0.000000000000000000000211758236813575084767080625169910490512847900390625L,
	0.0000000000000000000001058791184067875423835403125849552452564239501953125L,
	0.00000000000000000000005293955920339377119177015629247762262821197509765625L,
	0.000000000000000000000026469779601696885595885078146238811314105987548828125L,
	0.0000000000000000000000132348898008484427979425390731194056570529937744140625L,
	0.00000000000000000000000661744490042422139897126953655970282852649688720703125L,
	0.000000000000000000000003308722450212110699485634768279851414263248443603515625L,
	0.0000000000000000000000016543612251060553497428173841399257071316242218017578125L,
	0.00000000000000000000000082718061255302767487140869206996285356581211090087890625L,
	0.000000000000000000000000413590306276513837435704346034981426782906055450439453125L,
	0.0000000000000000000000002067951531382569187178521730174907133914530277252197265625L,
	0.00000000000000000000000010339757656912845935892608650874535669572651386260986328125L,
	0.000000000000000000000000051698788284564229679463043254372678347863256931304931640625L,
	0.0000000000000000000000000258493941422821148397315216271863391739316284656524658203125L,
	0.00000000000000000000000001292469707114105741986576081359316958696581423282623291015625L,
	0.000000000000000000000000006462348535570528709932880406796584793482907116413116455078125L,
	0.0000000000000000000000000032311742677852643549664402033982923967414535582065582275390625L,
	0.00000000000000000000000000161558713389263217748322010169914619837072677910327911376953125L,
	0.000000000000000000000000000807793566946316088741610050849573099185363389551639556884765625L,
	0.0000000000000000000000000004038967834731580443708050254247865495926816947758197784423828125L,
	0.00000000000000000000000000020194839173657902218540251271239327479634084738790988922119140625L,
	0.000000000000000000000000000100974195868289511092701256356196637398170423693954944610595703125L,
	0.0000000000000000000000000000504870979341447555463506281780983186990852118469774723052978515625L,
	0.00000000000000000000000000002524354896707237777317531408904915934954260592348873615264892578125L,
	0.000000000000000000000000000012621774483536188886587657044524579674771302961744368076324462890625L,
	0.0000000000000000000000000000063108872417680944432938285222622898373856514808721840381622314453125L,
	0.00000000000000000000000000000315544362088404722164691426113114491869282574043609201908111572265625L,
	0.000000000000000000000000000001577721810442023610823457130565572459346412870218046009540557861328125L,
	0.0000000000000000000000000000007888609052210118054117285652827862296732064351090230047702789306640625L,
	0.0000000000000000000000000000003944304526105059027058642826413931148366032175545115023851394653320312L,
	0.0000000000000000000000000000001972152263052529513529321413206965574183016087772557511925697326660156L,
	0.0000000000000000000000000000000986076131526264756764660706603482787091508043886278755962848663330078L,
	0.0000000000000000000000000000000493038065763132378382330353301741393545754021943139377981424331665039L,
	0.0000000000000000000000000000000246519032881566189191165176650870696772877010971569688990712165832520L,
	0.0000000000000000000000000000000123259516440783094595582588325435348386438505485784844495356082916260L,
	0.0000000000000000000000000000000061629758220391547297791294162717674193219252742892422247678041458130L,
	0.0000000000000000000000000000000030814879110195773648895647081358837096609626371446211123839020729065L,
	0.0000000000000000000000000000000015407439555097886824447823540679418548304813185723105561919510364532L,
	0.0000000000000000000000000000000007703719777548943412223911770339709274152406592861552780959755182266L,
	0.0000000000000000000000000000000003851859888774471706111955885169854637076203296430776390479877591133L,
	0.0000000000000000000000000000000001925929944387235853055977942584927318538101648215388195239938795567L,
	0.0000000000000000000000000000000000962964972193617926527988971292463659269050824107694097619969397783L,
	0.0000000000000000000000000000000000481482486096808963263994485646231829634525412053847048809984698892L,
	0.0000000000000000000000000000000000240741243048404481631997242823115914817262706026923524404992349446L,
	0.0000000000000000000000000000000000120370621524202240815998621411557957408631353013461762202496174723L,
	0.0000000000000000000000000000000000060185310762101120407999310705778978704315676506730881101248087361L,
	0.0000000000000000000000000000000000030092655381050560203999655352889489352157838253365440550624043681L,
	0.0000000000000000000000000000000000015046327690525280101999827676444744676078919126682720275312021840L,
	0.0000000000000000000000000000000000007523163845262640050999913838222372338039459563341360137656010920L,
	0.0000000000000000000000000000000000003761581922631320025499956919111186169019729781670680068828005460L,
	0.0000000000000000000000000000000000001880790961315660012749978459555593084509864890835340034414002730L,
	0.0000000000000000000000000000000000000940395480657830006374989229777796542254932445417670017207001365L,
	0.0000000000000000000000000000000000000470197740328915003187494614888898271127466222708835008603500683L,
	0.0000000000000000000000000000000000000235098870164457501593747307444449135563733111354417504301750341L,
	0.0000000000000000000000000000000000000117549435082228750796873653722224567781866555677208752150875171L,
	0.0000000000000000000000000000000000000058774717541114375398436826861112283890933277838604376075437585L,
	0.0000000000000000000000000000000000000029387358770557187699218413430556141945466638919302188037718793L
};

//The encoding for each binary alphabet value
const char HUFFMAN_CODES[ALPHABET_SIZE][MAX_HUFFCODE_LEN+1] = {
    "1",
    "10",
    "100",
    "1000",
    "10000",
    "100000",
    "1000000",
    "10000000",
    "100000000",
    "1000000000",
    "10000000000",
    "100000000000",
    "1000000000000",
    "10000000000000",
    "100000000000000",
    "1000000000000000",
    "10000000000000000",
    "100000000000000000",
    "1000000000000000000",
    "10000000000000000000",
    "100000000000000000000",
    "1000000000000000000000",
    "10000000000000000000000",
    "100000000000000000000000",
    "1000000000000000000000000",
    "10000000000000000000000000",
    "100000000000000000000000000",
    "1000000000000000000000000000",
    "10000000000000000000000000000",
    "100000000000000000000000000000",
    "1000000000000000000000000000000",
    "10000000000000000000000000000000",
    "100000000000000000000000000000000",
    "1000000000000000000000000000000000",
    "10000000000000000000000000000000000",
    "100000000000000000000000000000000000",
    "1000000000000000000000000000000000000",
    "10000000000000000000000000000000000000",
    "100000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
};

#endif