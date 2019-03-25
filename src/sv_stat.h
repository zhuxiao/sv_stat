#ifndef SV_STAT_H_
#define SV_STAT_H_

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <getopt.h>
#include <limits.h>
#include <sys/stat.h>

using namespace std;

#define ADJUST_SIZE		10

#define VAR_UNC				0	// uncertain
#define VAR_INS				1	// insertion
#define VAR_DEL				2	// deletion
#define VAR_DUP				3	// duplication
#define VAR_INV				4	// inversion
#define VAR_TRA				5	// translocation
#define VAR_BND				6	// BND
#define VAR_INV_TRA			7	// inverted translocation
#define VAR_MIX				10	// mixed variation
#define VAR_MNP				11	// MNP

#define MIN_DIF_SIZE		20
#define MAX_DIF_SIZE		1000

#define SUB_DIF_REG_SIZE	50

#define SV_SIZE_ARR_SIZE	2000


typedef struct {
	string chrname;
	size_t startPos, endPos;  // 1-based
	string chrname2;
	size_t startPos2, endPos2;  // 1-based
	bool overlapped;	// default: false
	bool validFlag;		// default: true
	size_t sv_type;
	int32_t sv_len;
}SV_item;

typedef struct {
	SV_item *sv_item1, *sv_item2;
	double dif_size, size_ratio;
}SV_pair;


void showUsage();
void showUsageConvert();
void showUsageStat();
int parseConvert(int argc, char **argv);
int parseStat(int argc, char **argv);
void SVStat(string &sv_file1, string &sv_file2);

void refRegSizeStat(string &user_file, string &standard_file, int32_t max_valid_reg_thres);
void refRegSizeStatOp(string &refRegSizeFinename, string &sv_file, int32_t max_valid_reg_thres);

void SVSizeDifStat(string &sv_file1, string &sv_file2, int32_t max_valid_reg_thres);
void SVSizeDifStatOp(string &sv_file1, string &sv_file2, int32_t max_valid_reg_thres);
vector<SV_pair*> computeOverlapSVPair(vector<SV_item*> &data1, vector<SV_item*> &data2);
void outputPairDataToFile(string &filename, vector<SV_pair*> &sv_pair_vec);
vector< vector<int32_t> > computeDifStatVec(vector<SV_pair*> &sv_pair_vec);
void outputDifStatToFile(string &svSizeDifStatFilename, vector< vector<int32_t> > &dif_stat_vec);
vector<size_t> computeRatioStatVec(vector<SV_pair*> &sv_pair_vec, vector<double> &ratio_div_vec);
void outputRatioStatToFile(string &svSizeRatioStatFilename_tmp, vector<size_t> &ratio_stat_vec, vector<double> &ratio_div_vec);

void SVNumStat(string &sv_file1, string &sv_file2, int32_t max_valid_reg_thres);
void SVNumStatOp(string &sv_file1, string &sv_file2, int32_t max_valid_reg_thres, string &dirname);
void computeNumStat(vector<SV_item*> &sv_data1, vector<SV_item*> &sv_data2, string &file_prefix);

void SVTypeNumStat(string &sv_file1, string &sv_file2, int32_t max_valid_reg_thres);
void SVTypeNumStatOp(string &sv_file1, string &sv_file2, vector<size_t> &size_div_vec, int32_t max_valid_reg_thres);
vector<vector<SV_item*>> sizeDivideSV(vector<SV_item*> &sv_data, vector<size_t> &size_div_vec);
void computeTypeNumStat(vector<vector<SV_item*>> &divided_vec1, vector<vector<SV_item*>> &divided_vec2);

void convertBed(const string &infilename, const string &outfilename, bool removeDuplicatedItemFlag);
void convertVcf(const string &infilename, const string &outfilename, bool removeDuplicatedItemFlag);
void convertCsv(const string &infilename, const string &outfilename, bool removeDuplicatedItemFlag);
void convertNm(const string &infilename, const string &outfilename, bool removeDuplicatedItemFlag);
string getSVType(vector<string> &str_vec);
int32_t getSVLen(vector<string> &str_vec, string &sv_type);
bool isSeq(string &seq);

SV_item *allocateSVItem(string &chrname, size_t startPos, size_t endPos, string &chrname2, size_t startPos2, size_t endPos2, string &sv_type_str, int32_t sv_len);
void removeDuplicatedSVItems(vector<SV_item*> &sv_item_vec);
void releaseSVItemVec(vector<SV_item*> &sv_item_vec);

vector<SV_item*> loadData(const string &filename);
void destroySizeDividedData(vector< vector<SV_item*> > &divided_vec);
void destroyData(vector<SV_item*> &sv_vec);
void destroyResultData(vector<vector<SV_item*>> &result);
void destroyPairData(vector<SV_pair*> &sv_vec);
vector<SV_item*> getLongSVReg(vector<SV_item*> &dataset, int32_t thres);
vector<vector<SV_item*>> intersect(vector<SV_item*> &data1, vector<SV_item*> &data2);
bool haveOverlap(SV_item* item1, SV_item* item2);
bool isOverlappedPos(size_t startPos1, size_t endPos1, size_t startPos2, size_t endPos2);
SV_item* itemdup(SV_item* item);
void output2File(const string &filename, vector<SV_item*> &data);
void computeLenStat(vector<SV_item*> &data, string &description_str);
vector<string> split(const string& s, const string& delim);
void printSV(vector<SV_item*> &data);

string double2Str(double num, int32_t fixedPrecision);


#endif /* SV_STAT_H_ */
