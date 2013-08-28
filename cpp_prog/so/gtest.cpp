#include <gtest/gtest.h>
//#include <>

bool validate(char* word){
    if(NULL==word){
		return false;
	}
	bool first = (unsigned char)(*word)>=0x81 && (unsigned char)(*word)<=0xFE;
	bool second = (unsigned char)(*(word+1))>=0x40 && (unsigned char)(*(word+1))<=0xFE;
	if((unsigned char)(*word)<=127){
		if(*word<32){
			return false;
		}else{
			return true;
		}
	}else if(first && second){
		return true;
	}else{
		return false;
	}
}

TEST(firstcase, control_char){
	char ctr[2];
	ctr[0]=0x15;
	ctr[1]=0;

	EXPECT_FALSE(validate(ctr));
}

TEST(firstcase, normal){
	char* eng="english";
	EXPECT_TRUE(validate(eng));
}

int main(int argc,char** argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}


