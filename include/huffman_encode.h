#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#define ALPHABET_SIZE 128

const long double ALPHABET[ALPHABET_SIZE] = {
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

const long double PROBABILITIES[ALPHABET_SIZE] = {
	0.5000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.2500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.1250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0625000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0312500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0156250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0078125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0039062500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0019531250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0009765625000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0004882812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0002441406250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0001220703125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000610351562500000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000305175781250000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000152587890625000000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000076293945312500000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000038146972656250000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000019073486328125000000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000009536743164062500000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000004768371582031250000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000002384185791015625000000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000001192092895507812500000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000596046447753906250000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000298023223876953125000000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000149011611938476562500000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000074505805969238281250000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000037252902984619140625000000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000018626451492309570312500000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000009313225746154785156250000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000004656612873077392578125000000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000002328306436538696289062500000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000001164153218269348144531250000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000000582076609134674072265625000000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000000291038304567337036132812500000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000000145519152283668518066406250000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000000072759576141834259033203125000000000000000000000000000000000000000000000000000000000000000L,
	0.0000000000036379788070917129516601562500000000000000000000000000000000000000000000000000000000000000L,
	0.0000000000018189894035458564758300781250000000000000000000000000000000000000000000000000000000000000L,
	0.0000000000009094947017729282379150390625000000000000000000000000000000000000000000000000000000000000L,
	0.0000000000004547473508864641189575195312500000000000000000000000000000000000000000000000000000000000L,
	0.0000000000002273736754432320594787597656250000000000000000000000000000000000000000000000000000000000L,
	0.0000000000001136868377216160297393798828125000000000000000000000000000000000000000000000000000000000L,
	0.0000000000000568434188608080148696899414062500000000000000000000000000000000000000000000000000000000L,
	0.0000000000000284217094304040074348449707031250000000000000000000000000000000000000000000000000000000L,
	0.0000000000000142108547152020037174224853515625000000000000000000000000000000000000000000000000000000L,
	0.0000000000000071054273576010018587112426757812500000000000000000000000000000000000000000000000000000L,
	0.0000000000000035527136788005009293556213378906250000000000000000000000000000000000000000000000000000L,
	0.0000000000000017763568394002504646778106689453125000000000000000000000000000000000000000000000000000L,
	0.0000000000000008881784197001252323389053344726562500000000000000000000000000000000000000000000000000L,
	0.0000000000000004440892098500626161694526672363281250000000000000000000000000000000000000000000000000L,
	0.0000000000000002220446049250313080847263336181640625000000000000000000000000000000000000000000000000L,
	0.0000000000000001110223024625156540423631668090820312500000000000000000000000000000000000000000000000L,
	0.0000000000000000555111512312578270211815834045410156250000000000000000000000000000000000000000000000L,
	0.0000000000000000277555756156289135105907917022705078125000000000000000000000000000000000000000000000L,
	0.0000000000000000138777878078144567552953958511352539062500000000000000000000000000000000000000000000L,
	0.0000000000000000069388939039072283776476979255676269531250000000000000000000000000000000000000000000L,
	0.0000000000000000034694469519536141888238489627838134765625000000000000000000000000000000000000000000L,
	0.0000000000000000017347234759768070944119244813919067382812500000000000000000000000000000000000000000L,
	0.0000000000000000008673617379884035472059622406959533691406250000000000000000000000000000000000000000L,
	0.0000000000000000004336808689942017736029811203479766845703125000000000000000000000000000000000000000L,
	0.0000000000000000002168404344971008868014905601739883422851562500000000000000000000000000000000000000L,
	0.0000000000000000001084202172485504434007452800869941711425781250000000000000000000000000000000000000L,
	0.0000000000000000000542101086242752217003726400434970855712890625000000000000000000000000000000000000L,
	0.0000000000000000000271050543121376108501863200217485427856445312500000000000000000000000000000000000L,
	0.0000000000000000000135525271560688054250931600108742713928222656250000000000000000000000000000000000L,
	0.0000000000000000000067762635780344027125465800054371356964111328125000000000000000000000000000000000L,
	0.0000000000000000000033881317890172013562732900027185678482055664062500000000000000000000000000000000L,
	0.0000000000000000000016940658945086006781366450013592839241027832031250000000000000000000000000000000L,
	0.0000000000000000000008470329472543003390683225006796419620513916015625000000000000000000000000000000L,
	0.0000000000000000000004235164736271501695341612503398209810256958007812500000000000000000000000000000L,
	0.0000000000000000000002117582368135750847670806251699104905128479003906250000000000000000000000000000L,
	0.0000000000000000000001058791184067875423835403125849552452564239501953125000000000000000000000000000L,
	0.0000000000000000000000529395592033937711917701562924776226282119750976562500000000000000000000000000L,
	0.0000000000000000000000264697796016968855958850781462388113141059875488281250000000000000000000000000L,
	0.0000000000000000000000132348898008484427979425390731194056570529937744140625000000000000000000000000L,
	0.0000000000000000000000066174449004242213989712695365597028285264968872070312500000000000000000000000L,
	0.0000000000000000000000033087224502121106994856347682798514142632484436035156250000000000000000000000L,
	0.0000000000000000000000016543612251060553497428173841399257071316242218017578125000000000000000000000L,
	0.0000000000000000000000008271806125530276748714086920699628535658121109008789062500000000000000000000L,
	0.0000000000000000000000004135903062765138374357043460349814267829060554504394531250000000000000000000L,
	0.0000000000000000000000002067951531382569187178521730174907133914530277252197265625000000000000000000L,
	0.0000000000000000000000001033975765691284593589260865087453566957265138626098632812500000000000000000L,
	0.0000000000000000000000000516987882845642296794630432543726783478632569313049316406250000000000000000L,
	0.0000000000000000000000000258493941422821148397315216271863391739316284656524658203125000000000000000L,
	0.0000000000000000000000000129246970711410574198657608135931695869658142328262329101562500000000000000L,
	0.0000000000000000000000000064623485355705287099328804067965847934829071164131164550781250000000000000L,
	0.0000000000000000000000000032311742677852643549664402033982923967414535582065582275390625000000000000L,
	0.0000000000000000000000000016155871338926321774832201016991461983707267791032791137695312500000000000L,
	0.0000000000000000000000000008077935669463160887416100508495730991853633895516395568847656250000000000L,
	0.0000000000000000000000000004038967834731580443708050254247865495926816947758197784423828125000000000L,
	0.0000000000000000000000000002019483917365790221854025127123932747963408473879098892211914062500000000L,
	0.0000000000000000000000000001009741958682895110927012563561966373981704236939549446105957031250000000L,
	0.0000000000000000000000000000504870979341447555463506281780983186990852118469774723052978515625000000L,
	0.0000000000000000000000000000252435489670723777731753140890491593495426059234887361526489257812500000L,
	0.0000000000000000000000000000126217744835361888865876570445245796747713029617443680763244628906250000L,
	0.0000000000000000000000000000063108872417680944432938285222622898373856514808721840381622314453125000L,
	0.0000000000000000000000000000031554436208840472216469142611311449186928257404360920190811157226562500L,
	0.0000000000000000000000000000015777218104420236108234571305655724593464128702180460095405578613281250L,
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


#endif
