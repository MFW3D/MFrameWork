//#include <iostream>
//#include "Common_Base.pb.h"
//#include <string>
//
//
//int main()
//{
//
//	PCommon_Base::MTest1 test1;
//	test1.set_a(11);
//	test1.set_a(14);
//
//	PCommon_Base::NetHead head;
//	head.set_cmd(1);
//	head.set_count(1);
//	head.set_index(1);
//	head.set_datalength(test1.ByteSize());
//	head.set_key(123456);
//
//	std::string dd = "";
//	head.SerializeToString(&dd);
//	std::string dd1 = "";
//	test1.SerializeToString(&dd1);
//	dd.append(dd1);
//
//
//	PCommon_Base::NetHead head1;
//
//	head1.ParseFromString(dd);
//
//	dd = dd.substr(head1.ByteSize(), head1.datalength());
//	test1.ParseFromString(dd);
//
//
//
//
//
//
//
//
//	return 0;
//}

