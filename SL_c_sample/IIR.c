/**
 *  @file IIR.c
 *
 *  @copyright Copyright (c) 2023 Pattern Recognition Lab where Sangmyung Univ all rights reserved.
 *
 *  @details inline function definitions
 *
 */

#include "IIR.h"

#define m 11

static const double BUFFER_BANDPASS_A[30][11] =
{
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 1
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 2
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 3
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 4
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 5
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 6
	{1.0, 0.6028798234770837, -1.3892246226806861, -0.5431785935540441, 1.4014051264515384, 0.3872180885945882, -0.6928430185528075, -0.10940400584582245, 0.20299463163785803, 0.015091009795040371, -0.02421304265466987},
{1.0, -0.8090258946670942, -0.4550301870881355, 0.1947248338636267, 0.8189315074913115, -0.31954172992243235, -0.2229632818842963, 0.03508394138416652, 0.08577195420197861, -0.009099455103938305, -0.007601795752742465},
{1.0, -1.9405767412344685, 1.496594179273184, -1.0333321552508545, 1.2791795166300601, -0.9418723488647542, 0.31382432356350864, -0.1133901228280986, 0.08448004748029028, -0.020429058280569304, -0.0009759194387855319},
{1.0, -2.855769030265746, 3.831370090532107, -3.7235805793596586, 3.3270437998227558, -2.4106385763859435, 1.2456976905584032, -0.5059389739928402, 0.18449389657792342, -0.043599440990750346, 0.0036556771322390235},
{1.0, -3.605199228277238, 6.236710035358968, -7.313709190338562, 6.7763781732097375, -4.979470322532986, 2.7798463985058004, -1.178481142076309, 0.38296569179714085, -0.08354013092844183, 0.00851482968025027},
{1.0, -4.226729269979687, 8.5646059239765, -11.378785146666832, 11.255301587847498, -8.557943068311364, 4.945298226554352, -2.1396033622996997, 0.6756998363129394, -0.1405447931466894, 0.014268651158376763},
{1.0, -4.74841303967901, 10.750213396927991, -15.633888224667235, 16.40742994559095, -12.935564371957557, 7.670839336397799, -3.3664778781202056, 1.0539352397122563, -0.21329378648012445, 0.02107290516534937},
{1.0, -5.191144249482644, 12.77053205047718, -19.898981011743917, 21.947703145916428, -17.88794376150077, 10.8472942072357, -4.819287864265972, 1.50584885782316, -0.2998218062853985, 0.02889291346798181},
{1.0, -5.570649368536952, 14.62332163529798, -24.065369051530062, 27.665587734920706, -23.217909028952093, 14.361526566112994, -6.4530303557650175, 2.018564933320971, -0.397966676386234, 0.03762096004995781},
{1.0, -5.898912759797861, 16.316241289070796, -28.07091729196853, 33.412623683896406, -28.766501926301835, 18.111665257132106, -8.224315656142554, 2.57956215183942, -0.505606108105416, 0.047125124845929414},
{1.0, -6.1851831375570105, 17.861226139840873, -31.883204438708596, 39.08772160254131, -34.41162170397211, 22.012231824751048, -10.09453988726752, 3.177441588617148, -0.6207791132680132, 0.0572712146479562},
{1.0, -6.436685895225401, 19.27158971842064, -35.48845785010138, 44.624426640180765, -40.062478704136694, 25.994441350676098, -12.030936925034176, 3.8022478507868054, -0.7417396778065053, 0.06793278365122205},
{1.0, -6.659131469947078, 20.560563553600428, -38.88439558244956, 49.98099930850975, -45.653328579479734, 30.004484967520305, -14.006531721079426, 4.445524462024068, -0.8669711814588548, 0.07899541471006628},
{1.0, -6.857082111063984, 21.74060023582237, -42.07563077937931, 55.13305619292945, -51.137805975861504, 34.00118032621041, -15.999593686649186, 5.100228781512977, -0.9951792105544988, 0.09035809927204055},
{1.0, -7.034219625992796, 22.82308182427562, -45.07073609006852, 60.06824421761814, -56.484238510246975, 37.95362385816884, -17.99291369188274, 5.760583259417075, -1.1252735229379973, 0.10193313425262693},
{1.0, -7.193543173911883, 23.818240750875717, -47.88037911965323, 64.78243887605889, -61.671941178003266, 41.83910056990231, -19.973067529284165, 6.421906672662597, -1.2563455261858623, 0.11364528498778759},
{1.0, -7.337517086035714, 24.735188533618512, -50.51614848160029, 69.27705209622047, -66.68835804126005, 45.641325999593256, -21.929740082985717, 7.080448418769882, -1.387644879122645, 0.12543062215535555},
{1.0, -7.468182572093087, 25.581995372084886, -52.989825367906256, 73.55713610191822, -71.52688954035514, 49.349013900208455, -23.855137753078765, 7.733236886240617, -1.5185571463716334, 0.13723525641924572},
{1.0, -7.587243030508715, 26.36578988801353, -55.3129425461242, 77.63005392112686, -76.18525582198959, 52.954731390192336, -25.743493331646228, 8.377946157323212, -1.648583434945078, 0.1490140914802049},
{1.0, -7.696129851517107, 27.092862751877067, -57.49652850488345, 81.50455176305351, -80.66427108723082, 56.453994763948984, -27.590656773652963, 9.01278168946195, -1.7773223632300454, 0.16072965735536063},
{1.0, -7.796053651713153, 27.76876596414132, -59.550970353713005, 85.1901159209194, -84.96692960550895, 59.84456087887122, -29.393761143061308, 9.636383830987409, -1.904454391425357, 0.1723510519086415},
{1.0, -7.888044518690698, 28.398403995115473, -61.48595224832273, 88.69653096770325, -89.0977265350123, 63.125874686842714, -31.1509521548869, 10.247747254348727, -2.0297283752624664, 0.18385299942253253},
{1.0, -7.972983886227146, 28.98611540588085, -63.310441140048745, 92.03358027607653, -93.06215500005821, 66.29864007832168, -32.86117041459122, 10.846154167952308, -2.1529501279459082, 0.19521502435912408},
{1.0, -8.05162997811639, 29.5357448550029, -65.03270144512248, 95.21084706794322, -96.86633521392665, 69.36448745766437, -34.52397675512116, 11.431119226611742, -2.2739727498239066, 0.20642073290272206},

};
static const double BUFFER_BANDPASS_B[30][11] =
{
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 1
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 2
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 3
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 4
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 5
	{0, 0, 0, 0, 0,0,0, 0, 0, 0, 0},  // fs 6
	{0.15605837198969877, 0.0, -0.7802918599484938, 0.0, 1.5605837198969876, 0.0, -1.5605837198969876, 0.0, 0.7802918599484938, 0.0, -0.15605837198969877},
{0.0915344328651308, 0.0, -0.457672164325654, 0.0, 0.915344328651308, 0.0, -0.915344328651308, 0.0, 0.457672164325654, 0.0, -0.0915344328651308},
{0.0575459098279655, 0.0, -0.2877295491398275, 0.0, 0.575459098279655, 0.0, -0.575459098279655, 0.0, 0.2877295491398275, 0.0, -0.0575459098279655},
{0.03804782707883597, 0.0, -0.19023913539417986, 0.0, 0.3804782707883597, 0.0, -0.3804782707883597, 0.0, 0.19023913539417986, 0.0, -0.03804782707883597},
{0.026149141338471807, 0.0, -0.13074570669235902, 0.0, 0.26149141338471804, 0.0, -0.26149141338471804, 0.0, 0.13074570669235902, 0.0, -0.026149141338471807},
{0.01853660554777469, 0.0, -0.09268302773887346, 0.0, 0.18536605547774693, 0.0, -0.18536605547774693, 0.0, 0.09268302773887346, 0.0, -0.01853660554777469},
{0.013479729104256396, 0.0, -0.06739864552128198, 0.0, 0.13479729104256397, 0.0, -0.13479729104256397, 0.0, 0.06739864552128198, 0.0, -0.013479729104256396},
{0.010015442468309248, 0.0, -0.050077212341546246, 0.0, 0.10015442468309249, 0.0, -0.10015442468309249, 0.0, 0.050077212341546246, 0.0, -0.010015442468309248},
{0.007580044300301093, 0.0, -0.03790022150150547, 0.0, 0.07580044300301093, 0.0, -0.07580044300301093, 0.0, 0.03790022150150547, 0.0, -0.007580044300301093},
{0.005829715438355661, 0.0, -0.029148577191778303, 0.0, 0.05829715438355661, 0.0, -0.05829715438355661, 0.0, 0.029148577191778303, 0.0, -0.005829715438355661},
{0.00454740860879459, 0.0, -0.02273704304397295, 0.0, 0.0454740860879459, 0.0, -0.0454740860879459, 0.0, 0.02273704304397295, 0.0, -0.00454740860879459},
{0.003592035249578844, 0.0, -0.01796017624789422, 0.0, 0.03592035249578844, 0.0, -0.03592035249578844, 0.0, 0.01796017624789422, 0.0, -0.003592035249578844},
{0.002869534189211378, 0.0, -0.014347670946056889, 0.0, 0.028695341892113778, 0.0, -0.028695341892113778, 0.0, 0.014347670946056889, 0.0, -0.002869534189211378},
{0.002315794119702396, 0.0, -0.01157897059851198, 0.0, 0.02315794119702396, 0.0, -0.02315794119702396, 0.0, 0.01157897059851198, 0.0, -0.002315794119702396},
{0.0018862543994411943, 0.0, -0.009431271997205972, 0.0, 0.018862543994411944, 0.0, -0.018862543994411944, 0.0, 0.009431271997205972, 0.0, -0.0018862543994411943},
{0.0015493980181572006, 0.0, -0.0077469900907860025, 0.0, 0.015493980181572005, 0.0, -0.015493980181572005, 0.0, 0.0077469900907860025, 0.0, -0.0015493980181572006},
{0.0012825810789606855, 0.0, -0.006412905394803428, 0.0, 0.012825810789606856, 0.0, -0.012825810789606856, 0.0, 0.006412905394803428, 0.0, -0.0012825810789606855},
{0.0010693020524001739, 0.0, -0.005346510262000869, 0.0, 0.010693020524001739, 0.0, -0.010693020524001739, 0.0, 0.005346510262000869, 0.0, -0.0010693020524001739},
{0.000897379108195796, 0.0, -0.00448689554097898, 0.0, 0.00897379108195796, 0.0, -0.00897379108195796, 0.0, 0.00448689554097898, 0.0, -0.000897379108195796},
{0.0007577122647375752, 0.0, -0.003788561323687876, 0.0, 0.007577122647375752, 0.0, -0.007577122647375752, 0.0, 0.003788561323687876, 0.0, -0.0007577122647375752},
{0.0006434293448948848, 0.0, -0.003217146724474424, 0.0, 0.006434293448948848, 0.0, -0.006434293448948848, 0.0, 0.003217146724474424, 0.0, -0.0006434293448948848},
{0.0005492881750553876, 0.0, -0.002746440875276938, 0.0, 0.005492881750553876, 0.0, -0.005492881750553876, 0.0, 0.002746440875276938, 0.0, -0.0005492881750553876},
{0.00047125256434531914, 0.0, -0.0023562628217265956, 0.0, 0.004712525643453191, 0.0, -0.004712525643453191, 0.0, 0.0023562628217265956, 0.0, -0.00047125256434531914},
{0.00040618784757059565, 0.0, -0.0020309392378529785, 0.0, 0.004061878475705957, 0.0, -0.004061878475705957, 0.0, 0.0020309392378529785, 0.0, -0.00040618784757059565},
};

void EsrcMath_Vector_Zeroize(double* v, int n)
{
	for (int i = 0; i < n; i++) {
		v[i] = 0;
	}
}

void IIR_Ifilter(const double* x, double* y, int n, const double* a, const double* b);


/*------------------------------------------------------------------------------*\
 *	@FunctionName::	EsrcDSP_IIR_Bandpass
 *
 *	@Description ::	Apply Bandpass filter on signal
 *
 *	@Input		 ::
 *					pSignal: Input signal (Length)
 *					Length: Length ot signal
 *					fs: Frame per second
 *	@Output		 ::
 *					pBandpassSignal: Result signal (Length)
 *	@Return		 ::
 *					None
\*------------------------------------------------------------------------------*/
void EsrcDSP_IIR_Bandpass(const double* pSignal, double* pBandpassSignal, int Length, int fs)
{
	// Bandpass (0.75~2.5 Hz, 5 order)
	IIR_Ifilter(pSignal, pBandpassSignal, Length, BUFFER_BANDPASS_A[fs - 1], BUFFER_BANDPASS_B[fs - 1]);
}

/*------------------------------------------------------------------------------*\
 *	@FunctionName::	IIR_Ifilter
 *
 *	@Description ::	Apply IIR filter on signal
 *
 *	@Input		 ::
 *					x: Input signal (n)
 *					n: Length ot signal
 *					a: A parameters of filter
 *					b: B parameters of filter
 *					m: Order of filter
 *	@Output		 ::
 *					y: Result signal (n)
 *	@Return		 ::
 *					None
\*------------------------------------------------------------------------------*/
void IIR_Ifilter(const double* x, double* y, int n, const double* a, const double* b)
{
	// Zeroize
	EsrcMath_Vector_Zeroize(y, n);

	// Apply filter - original
	for (int i = 0; i < n; i++) {
		y[i] += b[0] * x[i];
		for (int j = 1; j < m; j++) {
			if ((int)i - (int)j >= 0) {
				y[i] += (b[j] * x[i - j] - a[j] * y[i - j]);
			}
		}
	}

}