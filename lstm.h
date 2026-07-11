#pragma once
#include "resource.h"

HDC hdcframe;
HBITMAP oldframe;
HBITMAP framebmp;
int* framebuf;

HDC hdcbackground;		HBITMAP oldbackground;	HBITMAP backgroundbmp;	int* backgroundbuf;
HWND hEdit = NULL;

int dispx = 1026;
int dispy = 594;
HFONT hfont0, hfont1;
short int timerate = 32;	//	rate for gui timer

bool showinput = 0;	//	show input field
char intext[512] = { 0 };
char outext[8][128] = { 0 };
unsigned long int rnd;
char stop = 0;	//	stop training flag


#define idim 96		//	input/output layer size
#define hidd 128	//	hidden layer size
#define wind 64		//	truncated BPTT depth, written for ^2 values
#define winp (wind + 1)
#define winm (wind - 1)

char b = 32; //  previous c
char ch;

//	[dest][source] keeps with [i][j] code structuring

float nno[idim][hidd];		//	weights output layer
float obias[idim];			//	bias

float h0[winp][hidd] = { 0 };		//	hidden layer short term memory state
float c0[winp][hidd] = { 0 };		//	hidden layer long term memory state 'cell state'
float h0f[winp][hidd];		//	hidden layer forget gate
float h0i[winp][hidd];		//	hidden layer input gate
float h0m[winp][hidd];		//	hidden layer input node/potential memory activation
float h0o[winp][hidd];		//	hidden layer output gate

float nnh0hf[hidd][hidd];	//	weights hidden layer forget gate short term state
float nnh0hi[hidd][hidd];	//	weights hidden layer input gate short term state
float nnh0hm[hidd][hidd];	//	weights hidden layer input memory node short term state
float nnh0ho[hidd][hidd];	//	weights hidden layer output gate short term state

float nnh0if[hidd][idim];	//	weights hidden layer forget gate input
float nnh0ii[hidd][idim];	//	weights hidden layer input gate input
float nnh0im[hidd][idim];	//	weights hidden layer input memory node input
float nnh0io[hidd][idim];	//	weights hidden layer output gate input

float h0fbias[hidd];		//	bias hidden layer forget gate
float h0ibias[hidd];		//	bias hidden layer input gate
float h0mbias[hidd];		//	bias hidden layer input node/potential memory/candidate memory
float h0obias[hidd];		//	bias hidden layer output gate


float h[winp][hidd] = { 0 };		//	hidden layer short term memory state
float c[winp][hidd] = { 0 };		//	hidden layer long term memory state 'cell state'
float hf[winp][hidd];		//	hidden layer forget gate
float hi[winp][hidd];		//	hidden layer input gate
float hm[winp][hidd];		//	hidden layer input node/potential memory activation
float ho[winp][hidd];		//	hidden layer output gate

float nnhhf[hidd][hidd];	//	weights hidden layer forget gate short term state
float nnhhi[hidd][hidd];	//	weights hidden layer input gate short term state
float nnhhm[hidd][hidd];	//	weights hidden layer input memory node short term state
float nnhho[hidd][hidd];	//	weights hidden layer output gate short term state

float nnhif[hidd][hidd];	//	weights hidden layer forget gate input
float nnhii[hidd][hidd];	//	weights hidden layer input gate input
float nnhim[hidd][hidd];	//	weights hidden layer input memory node input
float nnhio[hidd][hidd];	//	weights hidden layer output gate input

float hfbias[hidd];			//	bias hidden layer forget gate
float hibias[hidd];			//	bias hidden layer input gate
float hmbias[hidd];			//	bias hidden layer input node/potential memory/candidate memory
float hobias[hidd];			//	bias hidden layer output gate



float dnno[idim][hidd];   //  so these three local variables are here instead
float dobias[idim];


float dh0[hidd];		//	deltas
float dh[hidd];

float dnnh0hf[hidd][hidd];
float dnnh0hi[hidd][hidd];
float dnnh0hm[hidd][hidd];
float dnnh0ho[hidd][hidd];

float dnnh0if[hidd][idim];	//	not hidd hidd
float dnnh0ii[hidd][idim];
float dnnh0im[hidd][idim];
float dnnh0io[hidd][idim];

float dh0fbias[hidd];
float dh0ibias[hidd];
float dh0mbias[hidd];
float dh0obias[hidd];


float dnnhhf[hidd][hidd];
float dnnhhi[hidd][hidd];
float dnnhhm[hidd][hidd];
float dnnhho[hidd][hidd];

float dnnhif[hidd][hidd];
float dnnhii[hidd][hidd];
float dnnhim[hidd][hidd];
float dnnhio[hidd][hidd];

float dhfbias[hidd];
float dhibias[hidd];
float dhmbias[hidd];
float dhobias[hidd];


int cin[wind];	//	was char.. input char per iteration

float netin[idim];		//  "hot one" array to input char - not actually used...
float netout[wind][idim];	//	outout/prediction


float dh0_next[hidd];
float dh_next[hidd];

float dc0_next[hidd];
float dc_next[hidd];

float dhf_raw[hidd];
float dhi_raw[hidd];
float dhm_raw[hidd];
float dho_raw[hidd];
float dh0f_raw[hidd];
float dh0i_raw[hidd];
float dh0m_raw[hidd];
float dh0o_raw[hidd];



bool GRADNORM = 1;	//	use gradient normalisation
bool ADAM = 0;	//	use ADAM optimisation
int adamt = 0;

const float beta1 = 0.9f;
const float beta2 = 0.999f;
const float beta1m = 0.1f;
const float beta2m = 0.001f;
const float epsilon = 1e-8f;	//	"try e-4 or e-3 to smooth stuck phases, -8 is indy default"

//	ADAM weight should be zeroed at model initialisation and kept for the entire training
//	they are not currently stored with the model so you gotta add it if you want it

float mnno[idim][hidd] = { 0 };
float mobias[idim] = { 0 };

float mnnh0hf[hidd][hidd] = { 0 };
float mnnh0hi[hidd][hidd] = { 0 };
float mnnh0hm[hidd][hidd] = { 0 };
float mnnh0ho[hidd][hidd] = { 0 };
float mnnh0if[hidd][idim] = { 0 };
float mnnh0ii[hidd][idim] = { 0 };
float mnnh0im[hidd][idim] = { 0 };
float mnnh0io[hidd][idim] = { 0 };
float mh0fbias[hidd] = { 0 };
float mh0ibias[hidd] = { 0 };
float mh0mbias[hidd] = { 0 };
float mh0obias[hidd] = { 0 };

float mnnhhf[hidd][hidd] = { 0 };
float mnnhhi[hidd][hidd] = { 0 };
float mnnhhm[hidd][hidd] = { 0 };
float mnnhho[hidd][hidd] = { 0 };
float mnnhif[hidd][hidd] = { 0 };
float mnnhii[hidd][hidd] = { 0 };
float mnnhim[hidd][hidd] = { 0 };
float mnnhio[hidd][hidd] = { 0 };
float mhfbias[hidd] = { 0 };
float mhibias[hidd] = { 0 };
float mhmbias[hidd] = { 0 };
float mhobias[hidd] = { 0 };


float vnno[idim][hidd] = { 0 };
float vobias[idim] = { 0 };

float vnnh0hf[hidd][hidd] = { 0 };
float vnnh0hi[hidd][hidd] = { 0 };
float vnnh0hm[hidd][hidd] = { 0 };
float vnnh0ho[hidd][hidd] = { 0 };
float vnnh0if[hidd][idim] = { 0 };
float vnnh0ii[hidd][idim] = { 0 };
float vnnh0im[hidd][idim] = { 0 };
float vnnh0io[hidd][idim] = { 0 };
float vh0fbias[hidd] = { 0 };
float vh0ibias[hidd] = { 0 };
float vh0mbias[hidd] = { 0 };
float vh0obias[hidd] = { 0 };

float vnnhhf[hidd][hidd] = { 0 };
float vnnhhi[hidd][hidd] = { 0 };
float vnnhhm[hidd][hidd] = { 0 };
float vnnhho[hidd][hidd] = { 0 };
float vnnhif[hidd][hidd] = { 0 };
float vnnhii[hidd][hidd] = { 0 };
float vnnhim[hidd][hidd] = { 0 };
float vnnhio[hidd][hidd] = { 0 };
float vhfbias[hidd] = { 0 };
float vhibias[hidd] = { 0 };
float vhmbias[hidd] = { 0 };
float vhobias[hidd] = { 0 };


unsigned long int tests = 0;
int thismany = 0;	//	setup for 10 training sessions
bool do10x = 0;

float learn = .01f;
float temp = 1.f;   //  temperature/confidence.. low values = higher repeats/confidence
float ebuf = 0.f;   //  error accumulator
float edisp = 0.f;   //  averaged display coefficient (e^edisp = # chars not sure)

char dispix = 0;	//	for stepping through colours :)

float learnarr[34] = {/*was28  .56234f,.31622f,.17782f,.1f,
	.056234f,.031622f,.017782f,.01f,
	5.6234e-3f, 3.1622e-3f, 1.7782e-3f, 1e-3f,
	5.6234e-4f, 3.1622e-4f, 1.7782e-4f, 1e-4f,
	5.6234e-5f, 3.1622e-5f, 1.7782e-5f, 1e-5f,
	5.6234e-6f, 3.1622e-6f, 1.7782e-6f, 1e-6f,
	5.6234e-7f, 3.1622e-7f, 1.7782e-7f, 1e-7f,*/
	0.5f,
	0.25f,
	0.125f, 0.1f,
	0.0625f,
	0.03125f,
	0.015625f, 0.01f,
	0.0078125f,
	0.00390625f,

	0.001953125f, 0.001f,
	0.0009765625f,
	0.00048828125f,
	0.000244140625f,
	0.0001220703125f, 0.0001f,
	0.00006103515625f,
	0.000030517578125f,
	0.0000152587890625f, 0.00001f,

	0.00000762939453125f,
	0.000003814697265625f,
	0.0000019073486328125f, 0.000001f,
	0.00000095367431640625f,
	0.000000476837158203125f,
	0.0000002384185791015625f,
	0.00000011920928955078125f, 0.0000001f,
	0.000000059604644775390625f,

	0.0000000298023223876953125f,
	0.00000001490116119384765625f, 0.00000001f
};
float regarr[31] = { 1e-4f, 3e-5f, 1e-5f, 3e-6f, 1e-6f, 3e-7f, 1e-7f, 3e-8f, 1e-8f, 3e-9f, 1e-9f,
1e-10f, 3e-11f, 1e-11f, 3e-12f, 1e-12f, 3e-13f, 1e-13f, 3e-14f, 1e-14f, 3e-15f, 1e-15f, 3e-16f, 1e-16f, 3e-17f, 1e-17f, 3e-18f, 1e-18f, 3e-19f, 1e-19f, 0.f };
float temparr[10] = { 1.f, .9f, .8f, .7f, .6f, .5f, .4f, .3f, .2f, .1f };
int learnix = 1;    //11  indexes for incrementing parameter value
int regix = 30;	//	was 19 of 20
int tempix = 0;

char out1[128];     //  gui display string
char out0[128];     //  target string

char displayindex = 0;


/*
//	i'm told - ok to change wind during training, not okay to turn onoff ADAM (needs continuous coefficients throughout)


regularisation "10-4 to 10-2 prevents overfitting.." L2 style regularization here.. ;) changes large error response
temperature = confidence or enthusiasm for learning the subject..
ADAM.. helps not get stuck in local minima

input and output use "one hot" arrays.. if you have 128 characters, you have 128 nodes, one is 1, the rest are 0
this seems to be a common way of formatting text information for RNN, using dynamic arrays and determining
the number of unique elements in your data, often applied at the word level rather than character.

using [enter] in .txt file results in 13, 10 (0d, 0a)
in practice EOF is byte 0 not 03 or anything else
.txt is created with no header on win10, first bytes are first CHAR
  0  NUL (null)                      32  SPACE     64  @         96  `
  1  SOH (start of heading)          33  !         65  A         97  a
  2  STX (start of text)             34  "         66  B         98  b
  3  ETX (end of text)               35  #         67  C         99  c
  4  EOT (end of transmission)       36  $         68  D        100  d
  5  ENQ (enquiry)                   37  %         69  E        101  e
  6  ACK (acknowledge)               38  &         70  F        102  f
  7  BEL (bell)                      39  '         71  G        103  g
  8  BS  (backspace)                 40  (         72  H        104  h
  9  TAB (horizontal tab)            41  )         73  I        105  i
 10  LF  (NL line feed, new line)    42  *         74  J        106  j
 11  VT  (vertical tab)              43  +         75  K        107  k
 12  FF  (NP form feed, new page)    44  ,         76  L        108  l
 13  CR  (carriage return)           45  -         77  M        109  m
 14  SO  (shift out)                 46  .         78  N        110  n
 15  SI  (shift in)                  47  /         79  O        111  o
 16  DLE (data link escape)          48  0         80  P        112  p
 17  DC1 (device control 1)          49  1         81  Q        113  q
 18  DC2 (device control 2)          50  2         82  R        114  r
 19  DC3 (device control 3)          51  3         83  S        115  s
 20  DC4 (device control 4)          52  4         84  T        116  t
 21  NAK (negative acknowledge)      53  5         85  U        117  u
 22  SYN (synchronous idle)          54  6         86  V        118  v
 23  ETB (end of trans. block)       55  7         87  W        119  w
 24  CAN (cancel)                    56  8         88  X        120  x
 25  EM  (end of medium)             57  9         89  Y        121  y
 26  SUB (substitute)                58  :         90  Z        122  z
 27  ESC (escape)                    59  ;         91  [        123  {
 28  FS  (file separator)            60  <         92  \        124  |
 29  GS  (group separator)           61  =         93  ]        125  }
 30  RS  (record separator)          62  >         94  ^        126  ~
 31  US  (unit separator)            63  ?         95  _        127  DEL

formatting	3	10, 13, 32 (lf, cr, space)
symbols		31	33-47	58-64	91-96	123-125
numerals	10	48-57 0-9
capitals	26	65-90
lowercase	26	97-122

*/