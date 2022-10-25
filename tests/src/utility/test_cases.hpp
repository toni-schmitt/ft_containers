#pragma once

#include "tests.hpp"
#include <string>

#define GET_TEST_CASE test_cases::get_test_case(value_type());
#define FILL_CONTAINER_WITH_TEST_CASE container_type(test_cases::get_test_case(value_type()), test_cases::get_test_case(value_type()) + test_cases::size);
#define TRY_CATCH_WRITE(x) try { (x); } catch (std::exception &e) { (*this->ofs) << e.what() << std::endl; }

struct test_cases
{
	static const int size = 100;

	static int *get_test_case(int int_test_case)
	{
		( void ) int_test_case;

		static int test_case[size] = {
				40600, 58369, 34651, 81793, 69933, 22900, 52497, 14860, 19943, 19665, 16873,
				93803, 96092, 69285, 29334, 37146, 75742, 99056, 96633, 532, 13847, 39412, 93642,
				55177, 69942, 23958, 13688, 21699, 8130, 81638, 67467, 43932, 95232, 75337,
				87256, 54793, 35048, 49401, 83007, 39016, 63560, 17924, 85561, 19415, 32787,
				85216, 22629, 1824, 12709, 97696, 39733, 44127, 47723, 63312, 84493, 39113,
				63939, 68586, 26262, 51290, 16827, 72069, 65180, 77604, 6681, 94816, 75935,
				82070, 83662, 49225, 61209, 89105, 64452, 52642, 28269, 413, 42182, 81417, 81050,
				9906, 57558, 73892, 12567, 30982, 95261, 12702, 4106, 22519, 58774, 33917, 38106,
				36535, 67885, 32921, 77196, 31890, 5411, 93606, 95748, 23524
		};

		return test_case;
	}

	static std::string *get_test_case(const std::string &string_test_case)
	{
		( void ) string_test_case;

		static std::string test_case[size] = {
				"rh@8$EZ8jWUr3vk#WQWT", "dX78m&819zWs59p4oO$f", "HeWF2S$jGamB#w&3jdYZ",
				"TV&V9O7&MvgxcYzaOyeE", "b6TA*!sNs=$R@sEhCcgP", "$p+#bAQTPmovKGRJv3@a",
				"MxHWcAswBnNP1OMMJ=Xc", "!aGZaDHDPnF=WgRUn$rn", "jOBxC2EJ7t*njjQcJKND",
				"Dfgvp85kOD4P*nn+$b3F", "3j%3mXXR1fWsrA!!BohG", "EbGKjUUN07rn0SHns$=Y",
				"1vb3J&U#T*hRerNPOBxg", "fe+3SGsk6y7HMx&GAo$=", "%yw+7MA#Yt5$NTgVy+DH",
				"j!KumTRMfMHq39z9O=Ev", "ZygRBKNXo&PW7x3+4nBx", "btgZP5Gth95nX%Q#fQUM",
				"fMuFUT!aHxor+PBGBMJd", "CyP@AbsP2KJp%#Uyq9Ty", "Qf2oc!rOwB*Wt57W5m!8",
				"uGYg%hvoasy6sN3csNTF", "SBzY&Wsof@W+rEy*=mbr", "B!+r@E5RrK#Hc2OXjh+F",
				"UJbyj=1BSGWyCTpyen2C", "Yb8X1FV6GB0xYzF&ZKc4", "qFKB9Sdm7hPcYRm$S+jw",
				"@EO$ECytUGkH=EC+NO#x", "Hatv39FYjqD0bfYUGT+e", "#bhG7Fy0HQYFThsn6xm1",
				"PKwM7abFq$uqpo!&%+k=", "71+3TTswsPr3eKY6Q5TT", "kN7rjuG&b*9rfB+3Pav#",
				"YD74J*9OFmHE&Suos673", "O!XbQn@sg=&@S#!yQhYN", "WtgbS$uC#A$!GRuBJ9wM",
				"N%f$Mo4$WEEmmzGY5SYZ", "hXW#WvgJ2$dOht6hpR1*", "0GDq7Vxk=w0!cRurPd#j",
				"tmU@yjWb*OfOnVSkUZYj", "rRvE*zNFryVB3T6@TKU=", "%U7+ec44MJGy!P5Nh4dj",
				"v@JXsYQ03u92O8%R29r!", "Sv=oD!W19PDR%1EOt3$u", "Kw#h2JZJqAHAp=Qz&!gn",
				"A4UrXRNCcv6#YcPVr8Qy", "mGy&jbHkV8RDj7p%fjwb", "xTbe3N3S*ge60ap%N9fC",
				"Zhf%ZogHBXr%GrJgRZzT", "T@R2uTU9!AJ4hASQZOAY", "=Fu0H10JujE9zShH*EvH",
				"+JyG$Tsw!O47Ha4f#7T1", "p#RQ0D&KjwGttqy46M@#", "JR4#&fJk9YQ8qSyhf$O$",
				"@krbvk0!XeF%AjVmcvJV", "V&w9Y*$qQAka!7aN%mF#", "tp&KpBpcb3EbS8E%rbV%",
				"0n@Rp@FuUpE1qrZ$@kCR", "SWvbOt*E%MSNy4vQMSD2", "UJNDqZFNoOT!e7D++9Gg",
				"Bwf*=NN+jXbB#HTV2WFs", "0H8EuPt#QOO5@b3W7Zk+", "oW*zKeGSGm3T!6UKAc6S",
				"H7t+BS=uceZ@ey8FnM1U", "@CAn*GKt##tk=5b8bY$j", "=@M4JRZAd@m&Qezn&9ud",
				"%W6=r@nEk4$86F$e6m9k", "=W#OVO63CYFTX*X776Fm", "8!BYA9P0kesN#prYd#Ec",
				"b4q%U1J1fHbUaw7dquA$", "%&zvokc9GbS+X%*aDDnU", "hvkbhEOO+ewZM@P85CZP",
				"s7FZO+3YHg=sRTdrxKT1", "a0xZ%xRRsbEMW3OO2x=7", "AqyO#*vsZjZacHdckbO#",
				"q5wZ3boBnvYgVg#YCzsj", "KtxyPNHgTXXnHvBsg$Fp", "hqQA84aMQGuZ6&WpSbKN",
				"NDcxJDu24ny9W54#uu$z", "T#meexEsC0udOyuD*Uu9", "nDk&h1SYQp&A+0pJRJnQ",
				"X8R4+rSwT$%F2cQb8$Jw", "SYEE46w&XNfZ85QyqPN!", "*WFspC9EM%GF!yb52MF*",
				"RjOKS6V$3CuM*g+dbfWX", "D+hBd3h+PNz8awT1%3!U", "$82hQTOHh=jFjgw4JEza",
				"pEBEf*kEb37CxuYkxBX!", "fmq6TAt*OzRPdR9*yJ+d", "VYDcAnRSrcO+xr45ga+5",
				"SOdq3PkX5CJp*#MW3t3S", "fw%QxvoXAH+pu&v$rDcP", "k!=CK0Gj4%4ve&U=y5u+",
				"%U5xV1vWWt3Yb6nQ2Ruw", "jb%jox=z+ZwvMfZJD9%$", "T=EPQqeFVMS+BE$X!*4&",
				"8QZgyCP7D4XP5mzW31af", "W$2VKpPn@Yf1v#V9e0!W", "DYxp9f=PVDcb%ZQqFb5p",
				"9d6CvN*kC5fF6+7fDBEx"
		};

		return test_case;
	}

	static std::pair<const int, int> *get_test_case(std::pair<const int, int> int_pair_test_case)
	{
		( void ) int_pair_test_case;
		typedef std::pair<const int, int>::first_type first_type;
		typedef std::pair<const int, int>::second_type second_type;
		return _get_pair_test_case_std<const int, int>(first_type(), second_type());
	}

	static std::pair<const std::string, std::string> *
	get_test_case(std::pair<const std::string, std::string> string_pair_test_case)
	{
		( void ) string_pair_test_case;
		typedef std::pair<const std::string, std::string>::first_type first_type;
		typedef std::pair<const std::string, std::string>::second_type second_type;
		return _get_pair_test_case_std<const std::string, std::string>(first_type(), second_type());
	}

	static ft::pair<const int, int> *get_test_case(ft::pair<const int, int> int_pair_test_case)
	{
		( void ) int_pair_test_case;
		typedef ft::pair<const int, int>::first_type first_type;
		typedef ft::pair<const int, int>::second_type second_type;
		return _get_pair_test_case_ft<const int, int>(first_type(), second_type());
	}

	static ft::pair<const std::string, std::string> *
	get_test_case(ft::pair<const std::string, std::string> string_pair_test_case)
	{
		( void ) string_pair_test_case;
		typedef ft::pair<const std::string, std::string>::first_type first_type;
		typedef ft::pair<const std::string, std::string>::second_type second_type;
		return _get_pair_test_case_ft<const std::string, std::string>(first_type(), second_type());
	}

private:
	template < class T1, class T2 >
	static std::pair<T1, T2> *_get_pair_test_case_std(T1 pair_value, T2 pair_key)
	{
		std::srand(get_test_case(int())[ 0 ]);

		typedef typename std::pair<T1, T2> make_pair;

		static std::pair<T1, T2> test_case[size] = {
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
		};
		return test_case;
	}

	template < class T1, class T2 >
	static ft::pair<T1, T2> *_get_pair_test_case_ft(T1 pair_value, T2 pair_key)
	{
		std::srand(get_test_case(int())[ 0 ]);

		typedef typename ft::pair<T1, T2> make_pair;

		static ft::pair<T1, T2> test_case[size] = {
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
				make_pair(get_test_case(pair_value)[ std::rand() % 100 ], get_test_case(pair_key)[ std::rand() % 100 ]),
		};
		return test_case;
	}

};