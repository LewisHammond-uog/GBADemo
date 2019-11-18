//
// Ray Step Distance Look up table; 
// Number of Entries: 1442
// Stored as fixed point values with12 decimal bits
//

const int rayXStepDistance_lut[1442]=
{
	0x00000000, 0x0394ba08, 0x01ca5ac6, 0x01318f5e, 0x00e528eb, 0x00b75140, 0x0098c0fb, 0x0082ebca, 0x00728b85, 0x0065ce8a, 
	0x005b9d74, 0x0053467a, 0x004c5315, 0x00467136, 0x00416640, 0x003d0738, 0x003933e1, 0x0035d395, 0x0032d327, 0x00302374, 
	0x002db85f, 0x002b881c, 0x00298aa5, 0x0027b95a, 0x00260eb5, 0x00248613, 0x00231b88, 0x0021cbbb, 0x002093cf, 0x001f714c, 
	0x001e620d, 0x001d6435, 0x001c7623, 0x001b9667, 0x001ac3be, 0x0019fd08, 0x00194148, 0x00188f98, 0x0017e72e, 0x00174754, 
	0x0016af64, 0x00161ecb, 0x00159502, 0x00151190, 0x00149405, 0x00141bfe, 0x0013a91f, 0x00133b11, 0x0012d18a, 0x00126c42, 
	0x00120af7, 0x0011ad6d, 0x0011536e, 0x0010fcc5, 0x0010a944, 0x001058be, 0x00100b0a, 0x000fc002, 0x000f7783, 0x000f316c, 
	0x000eed9e, 0x000eabfd, 0x000e6c6c, 0x000e2ed4, 0x000df31c, 0x000db92f, 0x000d80f7, 0x000d4a61, 0x000d155a, 0x000ce1d1, 
	0x000cafb6, 0x000c7ef9, 0x000c4f8c, 0x000c2160, 0x000bf469, 0x000bc89b, 0x000b9de9, 0x000b7449, 0x000b4baf, 0x000b2413, 
	0x000afd6a, 0x000ad7ac, 0x000ab2d0, 0x000a8ecd, 0x000a6b9c, 0x000a4936, 0x000a2793, 0x000a06ad, 0x0009e67d, 0x0009c6fd, 
	0x0009a827, 0x000989f6, 0x00096c64, 0x00094f6c, 0x00093309, 0x00091737, 0x0008fbf1, 0x0008e132, 0x0008c6f6, 0x0008ad3a, 
	0x000893f9, 0x00087b30, 0x000862dc, 0x00084af8, 0x00083382, 0x00081c77, 0x000805d3, 0x0007ef94, 0x0007d9b6, 0x0007c438, 
	0x0007af15, 0x00079a4d, 0x000785dd, 0x000771c1, 0x00075df9, 0x00074a81, 0x00073758, 0x0007247b, 0x000711e9, 0x0006ffa0, 
	0x0006ed9e, 0x0006dbe1, 0x0006ca68, 0x0006b930, 0x0006a838, 0x0006977f, 0x00068704, 0x000676c3, 0x000666be, 0x000656f1, 
	0x0006475b, 0x000637fc, 0x000628d2, 0x000619dc, 0x00060b18, 0x0005fc86, 0x0005ee24, 0x0005dff2, 0x0005d1ed, 0x0005c417, 
	0x0005b66c, 0x0005a8ed, 0x00059b98, 0x00058e6c, 0x0005816a, 0x0005748f, 0x000567db, 0x00055b4d, 0x00054ee4, 0x000542a0, 
	0x00053680, 0x00052a83, 0x00051ea9, 0x000512f0, 0x00050758, 0x0004fbe0, 0x0004f088, 0x0004e550, 0x0004da36, 0x0004cf39, 
	0x0004c45b, 0x0004b999, 0x0004aef3, 0x0004a469, 0x000499fa, 0x00048fa5, 0x0004856b, 0x00047b4b, 0x00047144, 0x00046756, 
	0x00045d80, 0x000453c1, 0x00044a1b, 0x0004408b, 0x00043712, 0x00042daf, 0x00042462, 0x00041b2a, 0x00041207, 0x000408f9, 
	0x00040000, 0x0003f71a, 0x0003ee48, 0x0003e589, 0x0003dcdd, 0x0003d444, 0x0003cbbd, 0x0003c348, 0x0003bae5, 0x0003b293, 
	0x0003aa52, 0x0003a222, 0x00039a03, 0x000391f4, 0x000389f5, 0x00038206, 0x00037a26, 0x00037255, 0x00036a94, 0x000362e1, 
	0x00035b3c, 0x000353a6, 0x00034c1e, 0x000344a4, 0x00033d37, 0x000335d8, 0x00032e86, 0x00032741, 0x00032009, 0x000318dd, 
	0x000311be, 0x00030aaa, 0x000303a3, 0x0002fca8, 0x0002f5b8, 0x0002eed3, 0x0002e7fa, 0x0002e12c, 0x0002da69, 0x0002d3b1, 
	0x0002cd03, 0x0002c65f, 0x0002bfc6, 0x0002b937, 0x0002b2b2, 0x0002ac37, 0x0002a5c5, 0x00029f5d, 0x000298fe, 0x000292a8, 
	0x00028c5c, 0x00028618, 0x00027fdd, 0x000279ab, 0x00027382, 0x00026d60, 0x00026748, 0x00026137, 0x00025b2e, 0x0002552d, 
	0x00024f34, 0x00024943, 0x00024359, 0x00023d77, 0x0002379c, 0x000231c9, 0x00022bfc, 0x00022637, 0x00022078, 0x00021ac0, 
	0x0002150f, 0x00020f65, 0x000209c1, 0x00020423, 0x0001fe8c, 0x0001f8fb, 0x0001f370, 0x0001edeb, 0x0001e86c, 0x0001e2f3, 
	0x0001dd7f, 0x0001d812, 0x0001d2a9, 0x0001cd47, 0x0001c7ea, 0x0001c292, 0x0001bd3f, 0x0001b7f1, 0x0001b2a9, 0x0001ad66, 
	0x0001a827, 0x0001a2ed, 0x00019db9, 0x00019888, 0x0001935d, 0x00018e36, 0x00018913, 0x000183f5, 0x00017edb, 0x000179c6, 
	0x000174b4, 0x00016fa7, 0x00016a9e, 0x00016598, 0x00016097, 0x00015b99, 0x000156a0, 0x000151aa, 0x00014cb7, 0x000147c8, 
	0x000142dd, 0x00013df5, 0x00013911, 0x00013430, 0x00012f52, 0x00012a78, 0x000125a0, 0x000120cc, 0x00011bfa, 0x0001172c, 
	0x00011261, 0x00010d98, 0x000108d3, 0x00010410, 0x0000ff4f, 0x0000fa92, 0x0000f5d7, 0x0000f11e, 0x0000ec68, 0x0000e7b5, 
	0x0000e303, 0x0000de55, 0x0000d9a8, 0x0000d4fe, 0x0000d055, 0x0000cbaf, 0x0000c70b, 0x0000c269, 0x0000bdc9, 0x0000b92b, 
	0x0000b48f, 0x0000aff4, 0x0000ab5b, 0x0000a6c4, 0x0000a22f, 0x00009d9b, 0x00009909, 0x00009479, 0x00008fe9, 0x00008b5c, 
	0x000086cf, 0x00008244, 0x00007dbb, 0x00007932, 0x000074ab, 0x00007025, 0x00006ba0, 0x0000671c, 0x00006299, 0x00005e17, 
	0x00005996, 0x00005516, 0x00005097, 0x00004c18, 0x0000479a, 0x0000431d, 0x00003ea1, 0x00003a25, 0x000035aa, 0x0000312f, 
	0x00002cb5, 0x0000283b, 0x000023c2, 0x00001f49, 0x00001ad0, 0x00001658, 0x000011df, 0x00000d67, 0x000008ef, 0x00000477, 
	0x00000000, 0xfffffb89, 0xfffff711, 0xfffff299, 0xffffee21, 0xffffe9a8, 0xffffe530, 0xffffe0b7, 0xffffdc3e, 0xffffd7c5, 
	0xffffd34b, 0xffffced1, 0xffffca56, 0xffffc5db, 0xffffc15f, 0xffffbce3, 0xffffb866, 0xffffb3e8, 0xffffaf69, 0xffffaaea, 
	0xffffa66a, 0xffffa1e9, 0xffff9d67, 0xffff98e4, 0xffff9460, 0xffff8fdb, 0xffff8b55, 0xffff86ce, 0xffff8245, 0xffff7dbc, 
	0xffff7931, 0xffff74a4, 0xffff7017, 0xffff6b87, 0xffff66f7, 0xffff6265, 0xffff5dd1, 0xffff593c, 0xffff54a5, 0xffff500c, 
	0xffff4b71, 0xffff46d5, 0xffff4237, 0xffff3d97, 0xffff38f5, 0xffff3451, 0xffff2fab, 0xffff2b02, 0xffff2658, 0xffff21ab, 
	0xffff1cfd, 0xffff184b, 0xffff1398, 0xffff0ee2, 0xffff0a29, 0xffff056e, 0xffff00b1, 0xfffefbf0, 0xfffef72d, 0xfffef268, 
	0xfffeed9f, 0xfffee8d4, 0xfffee405, 0xfffedf34, 0xfffeda60, 0xfffed588, 0xfffed0ae, 0xfffecbd0, 0xfffec6ef, 0xfffec20b, 
	0xfffebd23, 0xfffeb838, 0xfffeb349, 0xfffeae56, 0xfffea960, 0xfffea467, 0xfffe9f69, 0xfffe9a68, 0xfffe9562, 0xfffe9059, 
	0xfffe8b4c, 0xfffe863a, 0xfffe8125, 0xfffe7c0b, 0xfffe76ed, 0xfffe71ca, 0xfffe6ca3, 0xfffe6778, 0xfffe6247, 0xfffe5d13, 
	0xfffe57d9, 0xfffe529a, 0xfffe4d57, 0xfffe480f, 0xfffe42c1, 0xfffe3d6e, 0xfffe3816, 0xfffe32b9, 0xfffe2d57, 0xfffe27ee, 
	0xfffe2281, 0xfffe1d0d, 0xfffe1794, 0xfffe1215, 0xfffe0c90, 0xfffe0705, 0xfffe0174, 0xfffdfbdd, 0xfffdf63f, 0xfffdf09b, 
	0xfffdeaf1, 0xfffde540, 0xfffddf88, 0xfffdd9c9, 0xfffdd404, 0xfffdce37, 0xfffdc864, 0xfffdc289, 0xfffdbca7, 0xfffdb6bd, 
	0xfffdb0cc, 0xfffdaad3, 0xfffda4d2, 0xfffd9ec9, 0xfffd98b8, 0xfffd92a0, 0xfffd8c7e, 0xfffd8655, 0xfffd8023, 0xfffd79e8, 
	0xfffd73a4, 0xfffd6d58, 0xfffd6702, 0xfffd60a3, 0xfffd5a3b, 0xfffd53c9, 0xfffd4d4e, 0xfffd46c9, 0xfffd403a, 0xfffd39a1, 
	0xfffd32fd, 0xfffd2c4f, 0xfffd2597, 0xfffd1ed4, 0xfffd1806, 0xfffd112c, 0xfffd0a48, 0xfffd0358, 0xfffcfc5d, 0xfffcf556, 
	0xfffcee42, 0xfffce723, 0xfffcdff7, 0xfffcd8bf, 0xfffcd17a, 0xfffcca28, 0xfffcc2c8, 0xfffcbb5c, 0xfffcb3e2, 0xfffcac5a, 
	0xfffca4c4, 0xfffc9d1f, 0xfffc956c, 0xfffc8dab, 0xfffc85da, 0xfffc7dfa, 0xfffc760b, 0xfffc6e0c, 0xfffc65fd, 0xfffc5dde, 
	0xfffc55ae, 0xfffc4d6d, 0xfffc451b, 0xfffc3cb8, 0xfffc3443, 0xfffc2bbc, 0xfffc2323, 0xfffc1a77, 0xfffc11b8, 0xfffc08e6, 
	0xfffc0000, 0xfffbf707, 0xfffbedf9, 0xfffbe4d6, 0xfffbdb9e, 0xfffbd251, 0xfffbc8ee, 0xfffbbf75, 0xfffbb5e5, 0xfffbac3f, 
	0xfffba281, 0xfffb98aa, 0xfffb8ebc, 0xfffb84b5, 0xfffb7a95, 0xfffb705a, 0xfffb6606, 0xfffb5b97, 0xfffb510d, 0xfffb4667, 
	0xfffb3ba5, 0xfffb30c7, 0xfffb25ca, 0xfffb1ab0, 0xfffb0f78, 0xfffb0420, 0xfffaf8a8, 0xfffaed10, 0xfffae157, 0xfffad57d, 
	0xfffac980, 0xfffabd5f, 0xfffab11c, 0xfffaa4b3, 0xfffa9825, 0xfffa8b71, 0xfffa7e96, 0xfffa7193, 0xfffa6468, 0xfffa5713, 
	0xfffa4994, 0xfffa3be9, 0xfffa2e12, 0xfffa200e, 0xfffa11dc, 0xfffa037a, 0xfff9f4e8, 0xfff9e624, 0xfff9d72e, 0xfff9c804, 
	0xfff9b8a5, 0xfff9a90f, 0xfff99942, 0xfff9893c, 0xfff978fc, 0xfff96880, 0xfff957c8, 0xfff946d0, 0xfff93598, 0xfff9241f, 
	0xfff91262, 0xfff9005f, 0xfff8ee17, 0xfff8db85, 0xfff8c8a8, 0xfff8b57f, 0xfff8a207, 0xfff88e3f, 0xfff87a23, 0xfff865b3, 
	0xfff850ea, 0xfff83bc8, 0xfff8264a, 0xfff8106c, 0xfff7fa2d, 0xfff7e389, 0xfff7cc7e, 0xfff7b508, 0xfff79d24, 0xfff784d0, 
	0xfff76c07, 0xfff752c6, 0xfff7390a, 0xfff71ece, 0xfff7040f, 0xfff6e8c9, 0xfff6ccf6, 0xfff6b093, 0xfff6939c, 0xfff6760a, 
	0xfff657d9, 0xfff63903, 0xfff61983, 0xfff5f953, 0xfff5d86d, 0xfff5b6ca, 0xfff59464, 0xfff57133, 0xfff54d30, 0xfff52854, 
	0xfff50295, 0xfff4dbed, 0xfff4b450, 0xfff48bb7, 0xfff46217, 0xfff43765, 0xfff40b97, 0xfff3dea0, 0xfff3b074, 0xfff38106, 
	0xfff35049, 0xfff31e2e, 0xfff2eaa6, 0xfff2b5a0, 0xfff27f09, 0xfff246d1, 0xfff20ce4, 0xfff1d12c, 0xfff19394, 0xfff15404, 
	0xfff11261, 0xfff0ce93, 0xfff0887c, 0xfff03ffe, 0xffeff4f6, 0xffefa742, 0xffef56bc, 0xffef033a, 0xffeeac91, 0xffee5292, 
	0xffedf509, 0xffed93be, 0xffed2e75, 0xffecc4ed, 0xffec56e0, 0xffebe400, 0xffeb6bf9, 0xffeaee6f, 0xffea6afd, 0xffe9e136, 
	0xffe9509d, 0xffe8b8ae, 0xffe818d1, 0xffe77067, 0xffe6beb8, 0xffe602f8, 0xffe53c42, 0xffe46999, 0xffe389de, 0xffe29bc9, 
	0xffe19df1, 0xffe08eb3, 0xffdf6c30, 0xffde3444, 0xffdce478, 0xffdb79e8, 0xffd9f146, 0xffd846a1, 0xffd67556, 0xffd477e0, 
	0xffd2479d, 0xffcfdc89, 0xffcd2ccd, 0xffca2c5e, 0xffc6cc11, 0xffc2f8ba, 0xffbe99c3, 0xffb98ecf, 0xffb3acf4, 0xffacb993, 
	0xffa4629f, 0xff9a316a, 0xff8d7470, 0xff7d1430, 0xff673f06, 0xff48aece, 0xff1ad742, 0xfece6faa, 0xfe35a362, 0xfc6b3ff4, 
	0xd6d40000, 0xfc6b4958, 0xfe35a5bc, 0xfece70b6, 0xff1ad7d8, 0xff48af2e, 0xff673f48, 0xff7d1461, 0xff8d7496, 0xff9a3188, 
	0xffa462b7, 0xffacb9a7, 0xffb3ad04, 0xffb98ede, 0xffbe99be, 0xffc2f8c5, 0xffc6cc1b, 0xffca2c66, 0xffcd2cd4, 0xffcfdc90, 
	0xffd247a3, 0xffd477e5, 0xffd6755b, 0xffd846a6, 0xffd9f14a, 0xffdb79eb, 0xffdce47b, 0xffde3447, 0xffdf6c33, 0xffe08eb6, 
	0xffe19df4, 0xffe29bcb, 0xffe389e0, 0xffe4699c, 0xffe53c44, 0xffe602f9, 0xffe6beba, 0xffe77069, 0xffe818d5, 0xffe8b8af, 
	0xffe9509f, 0xffe9e137, 0xffea6afe, 0xffeaee70, 0xffeb6bfa, 0xffebe401, 0xffec56e1, 0xffecc4ee, 0xffed2e76, 0xffed93bf, 
	0xffedf50a, 0xffee5293, 0xffeeac92, 0xffef033b, 0xffef56bd, 0xffefa743, 0xffeff4f7, 0xfff03ffe, 0xfff0887d, 0xfff0ce94, 
	0xfff11263, 0xfff15404, 0xfff19395, 0xfff1d12d, 0xfff20ce4, 0xfff246d2, 0xfff27f0a, 0xfff2b5a0, 0xfff2eaa7, 0xfff31e2e, 
	0xfff3504a, 0xfff38107, 0xfff3b074, 0xfff3dea0, 0xfff40b96, 0xfff43765, 0xfff46217, 0xfff48bb8, 0xfff4b451, 0xfff4dbed, 
	0xfff50296, 0xfff52854, 0xfff54d31, 0xfff57134, 0xfff59464, 0xfff5b6cb, 0xfff5d86d, 0xfff5f953, 0xfff61983, 0xfff63904, 
	0xfff657d9, 0xfff6760a, 0xfff6939c, 0xfff6b094, 0xfff6ccf7, 0xfff6e8c9, 0xfff70410, 0xfff71ece, 0xfff7390a, 0xfff752c6, 
	0xfff76c07, 0xfff784d0, 0xfff79d24, 0xfff7b508, 0xfff7cc7e, 0xfff7e389, 0xfff7fa2d, 0xfff8106c, 0xfff8264a, 0xfff83bc8, 
	0xfff850eb, 0xfff865b3, 0xfff87a24, 0xfff88e3f, 0xfff8a207, 0xfff8b57f, 0xfff8c8a8, 0xfff8db85, 0xfff8ee17, 0xfff90060, 
	0xfff91262, 0xfff9241f, 0xfff93598, 0xfff946d0, 0xfff957c8, 0xfff96880, 0xfff978fc, 0xfff9893d, 0xfff99942, 0xfff9a90f, 
	0xfff9b8a5, 0xfff9c804, 0xfff9d72e, 0xfff9e625, 0xfff9f4e8, 0xfffa037a, 0xfffa11dc, 0xfffa200e, 0xfffa2e13, 0xfffa3bea, 
	0xfffa4994, 0xfffa5713, 0xfffa6468, 0xfffa7194, 0xfffa7e96, 0xfffa8b71, 0xfffa9825, 0xfffaa4b3, 0xfffab11c, 0xfffabd60, 
	0xfffac980, 0xfffad57d, 0xfffae157, 0xfffaed10, 0xfffaf8a8, 0xfffb0420, 0xfffb0f78, 0xfffb1ab0, 0xfffb25ca, 0xfffb30c7, 
	0xfffb3ba5, 0xfffb4668, 0xfffb510d, 0xfffb5b97, 0xfffb6606, 0xfffb705b, 0xfffb7a95, 0xfffb84b5, 0xfffb8ebc, 0xfffb98ab, 
	0xfffba281, 0xfffbac3f, 0xfffbb5e6, 0xfffbbf75, 0xfffbc8ef, 0xfffbd251, 0xfffbdb9f, 0xfffbe4d6, 0xfffbedf9, 0xfffbf707, 
	0xfffc0000, 0xfffc08e6, 0xfffc11b8, 0xfffc1a77, 0xfffc2323, 0xfffc2bbc, 0xfffc3443, 0xfffc3cb8, 0xfffc451b, 0xfffc4d6d, 
	0xfffc55ae, 0xfffc5dde, 0xfffc65fd, 0xfffc6e0c, 0xfffc760b, 0xfffc7dfa, 0xfffc85da, 0xfffc8dab, 0xfffc956c, 0xfffc9d1f, 
	0xfffca4c4, 0xfffcac5a, 0xfffcb3e2, 0xfffcbb5c, 0xfffcc2c8, 0xfffcca28, 0xfffcd17a, 0xfffcd8bf, 0xfffcdff7, 0xfffce723, 
	0xfffcee42, 0xfffcf556, 0xfffcfc5d, 0xfffd0358, 0xfffd0a48, 0xfffd112d, 0xfffd1806, 0xfffd1ed4, 0xfffd2597, 0xfffd2c4f, 
	0xfffd32fd, 0xfffd39a1, 0xfffd403a, 0xfffd46c9, 0xfffd4d4e, 0xfffd53ca, 0xfffd5a3b, 0xfffd60a3, 0xfffd6702, 0xfffd6d58, 
	0xfffd73a4, 0xfffd79e8, 0xfffd8023, 0xfffd8655, 0xfffd8c7f, 0xfffd92a0, 0xfffd98b8, 0xfffd9ec9, 0xfffda4d2, 0xfffdaad3, 
	0xfffdb0cc, 0xfffdb6bd, 0xfffdbca7, 0xfffdc289, 0xfffdc864, 0xfffdce37, 0xfffdd404, 0xfffdd9ca, 0xfffddf88, 0xfffde540, 
	0xfffdeaf1, 0xfffdf09b, 0xfffdf640, 0xfffdfbdd, 0xfffe0174, 0xfffe0705, 0xfffe0c90, 0xfffe1215, 0xfffe1794, 0xfffe1d0d, 
	0xfffe2281, 0xfffe27ef, 0xfffe2d57, 0xfffe32b9, 0xfffe3816, 0xfffe3d6e, 0xfffe42c1, 0xfffe480f, 0xfffe4d57, 0xfffe529a, 
	0xfffe57d9, 0xfffe5d13, 0xfffe6248, 0xfffe6778, 0xfffe6ca3, 0xfffe71ca, 0xfffe76ed, 0xfffe7c0b, 0xfffe8125, 0xfffe863b, 
	0xfffe8b4c, 0xfffe9059, 0xfffe9562, 0xfffe9a68, 0xfffe9f69, 0xfffea467, 0xfffea960, 0xfffeae56, 0xfffeb349, 0xfffeb838, 
	0xfffebd23, 0xfffec20b, 0xfffec6ef, 0xfffecbd0, 0xfffed0ae, 0xfffed588, 0xfffeda60, 0xfffedf34, 0xfffee406, 0xfffee8d4, 
	0xfffeed9f, 0xfffef268, 0xfffef72d, 0xfffefbf0, 0xffff00b1, 0xffff056e, 0xffff0a29, 0xffff0ee2, 0xffff1398, 0xffff184b, 
	0xffff1cfd, 0xffff21ab, 0xffff2658, 0xffff2b03, 0xffff2fab, 0xffff3451, 0xffff38f5, 0xffff3d97, 0xffff4237, 0xffff46d5, 
	0xffff4b71, 0xffff500c, 0xffff54a5, 0xffff593c, 0xffff5dd1, 0xffff6265, 0xffff66f7, 0xffff6b87, 0xffff7017, 0xffff74a4, 
	0xffff7931, 0xffff7dbc, 0xffff8245, 0xffff86ce, 0xffff8b55, 0xffff8fdb, 0xffff9460, 0xffff98e4, 0xffff9d67, 0xffffa1e9, 
	0xffffa66a, 0xffffaaea, 0xffffaf69, 0xffffb3e8, 0xffffb866, 0xffffbce3, 0xffffc15f, 0xffffc5db, 0xffffca56, 0xffffced1, 
	0xffffd34b, 0xffffd7c5, 0xffffdc3e, 0xffffe0b7, 0xffffe530, 0xffffe9a8, 0xffffee21, 0xfffff299, 0xfffff711, 0xfffffb89, 
	0x00000000, 0x00000477, 0x000008ef, 0x00000d67, 0x000011df, 0x00001658, 0x00001ad0, 0x00001f49, 0x000023c2, 0x0000283b, 
	0x00002cb5, 0x0000312f, 0x000035aa, 0x00003a25, 0x00003ea1, 0x0000431d, 0x0000479a, 0x00004c18, 0x00005097, 0x00005516, 
	0x00005996, 0x00005e17, 0x00006299, 0x0000671c, 0x00006ba0, 0x00007025, 0x000074ab, 0x00007932, 0x00007dbb, 0x00008244, 
	0x000086cf, 0x00008b5c, 0x00008fe9, 0x00009479, 0x00009909, 0x00009d9b, 0x0000a22f, 0x0000a6c4, 0x0000ab5c, 0x0000aff4, 
	0x0000b48f, 0x0000b92b, 0x0000bdc9, 0x0000c269, 0x0000c70b, 0x0000cbaf, 0x0000d055, 0x0000d4fe, 0x0000d9a8, 0x0000de55, 
	0x0000e303, 0x0000e7b5, 0x0000ec68, 0x0000f11e, 0x0000f5d7, 0x0000fa92, 0x0000ff4f, 0x00010410, 0x000108d3, 0x00010d98, 
	0x00011261, 0x0001172c, 0x00011bfb, 0x000120cc, 0x000125a0, 0x00012a78, 0x00012f52, 0x00013430, 0x00013911, 0x00013df5, 
	0x000142dd, 0x000147c8, 0x00014cb7, 0x000151aa, 0x000156a0, 0x00015b99, 0x00016097, 0x00016598, 0x00016a9e, 0x00016fa7, 
	0x000174b4, 0x000179c6, 0x00017edb, 0x000183f5, 0x00018913, 0x00018e36, 0x0001935d, 0x00019888, 0x00019db9, 0x0001a2ee, 
	0x0001a827, 0x0001ad66, 0x0001b2a9, 0x0001b7f2, 0x0001bd3f, 0x0001c292, 0x0001c7ea, 0x0001cd47, 0x0001d2a9, 0x0001d812, 
	0x0001dd7f, 0x0001e2f3, 0x0001e86c, 0x0001edeb, 0x0001f370, 0x0001f8fb, 0x0001fe8c, 0x00020423, 0x000209c1, 0x00020f65, 
	0x0002150f, 0x00021ac0, 0x00022078, 0x00022637, 0x00022bfc, 0x000231c9, 0x0002379c, 0x00023d77, 0x0002435a, 0x00024943, 
	0x00024f35, 0x0002552d, 0x00025b2e, 0x00026137, 0x00026747, 0x00026d60, 0x00027382, 0x000279ab, 0x00027fdd, 0x00028618, 
	0x00028c5c, 0x000292a8, 0x000298fe, 0x00029f5d, 0x0002a5c5, 0x0002ac37, 0x0002b2b2, 0x0002b937, 0x0002bfc6, 0x0002c65f, 
	0x0002cd03, 0x0002d3b1, 0x0002da69, 0x0002e12c, 0x0002e7fa, 0x0002eed3, 0x0002f5b8, 0x0002fca8, 0x000303a3, 0x00030aab, 
	0x000311be, 0x000318dd, 0x00032009, 0x00032741, 0x00032e86, 0x000335d8, 0x00033d38, 0x000344a4, 0x00034c1e, 0x000353a6, 
	0x00035b3c, 0x000362e1, 0x00036a94, 0x00037255, 0x00037a26, 0x00038206, 0x000389f5, 0x000391f4, 0x00039a03, 0x0003a223, 
	0x0003aa52, 0x0003b293, 0x0003bae5, 0x0003c348, 0x0003cbbd, 0x0003d444, 0x0003dcdd, 0x0003e589, 0x0003ee48, 0x0003f71a, 
	0x0003ffff, 0x000408f9, 0x00041207, 0x00041b2a, 0x00042462, 0x00042daf, 0x00043712, 0x0004408b, 0x00044a1b, 0x000453c1, 
	0x00045d80, 0x00046756, 0x00047144, 0x00047b4b, 0x0004856b, 0x00048fa6, 0x000499fa, 0x0004a469, 0x0004aef3, 0x0004b999, 
	0x0004c45b, 0x0004cf39, 0x0004da36, 0x0004e550, 0x0004f089, 0x0004fbe0, 0x00050758, 0x000512f0, 0x00051ea9, 0x00052a83, 
	0x00053680, 0x000542a0, 0x00054ee4, 0x00055b4d, 0x000567db, 0x0005748f, 0x0005816a, 0x00058e6d, 0x00059b98, 0x0005a8ed, 
	0x0005b66c, 0x0005c417, 0x0005d1ee, 0x0005dff2, 0x0005ee24, 0x0005fc86, 0x00060b18, 0x000619db, 0x000628d2, 0x000637fc, 
	0x0006475b, 0x000656f0, 0x000666be, 0x000676c3, 0x00068704, 0x00069780, 0x0006a838, 0x0006b930, 0x0006ca68, 0x0006dbe1, 
	0x0006ed9f, 0x0006ffa0, 0x000711ea, 0x0007247b, 0x00073758, 0x00074a81, 0x00075df9, 0x000771c2, 0x000785dd, 0x00079a4e, 
	0x0007af16, 0x0007c438, 0x0007d9b6, 0x0007ef94, 0x000805d4, 0x00081c77, 0x00083383, 0x00084af8, 0x000862dc, 0x00087b31, 
	0x000893fa, 0x0008ad3b, 0x0008c6f6, 0x0008e132, 0x0008fbf1, 0x00091738, 0x0009330a, 0x00094f6d, 0x00096c65, 0x000989f7, 
	0x0009a828, 0x0009c6fd, 0x0009e67e, 0x000a06ae, 0x000a2794, 0x000a4937, 0x000a6b9d, 0x000a8ecc, 0x000ab2cf, 0x000ad7ac, 
	0x000afd6a, 0x000b2413, 0x000b4baf, 0x000b7448, 0x000b9de9, 0x000bc89b, 0x000bf46a, 0x000c2160, 0x000c4f8c, 0x000c7ef9, 
	0x000cafb6, 0x000ce1d2, 0x000d155a, 0x000d4a61, 0x000d80f7, 0x000db92f, 0x000df31c, 0x000e2ed4, 0x000e6c6d, 0x000eabfd, 
	0x000eed9f, 0x000f316c, 0x000f7784, 0x000fc004, 0x00100b0a, 0x001058bf, 0x0010a944, 0x0010fcc7, 0x0011536e, 0x0011ad6f, 
	0x00120af9, 0x00126c43, 0x0012d18d, 0x00133b12, 0x0013a921, 0x00141bff, 0x00149408, 0x00151194, 0x00159504, 0x00161ecf, 
	0x0016af66, 0x00174758, 0x0017e730, 0x00188f9c, 0x0019414e, 0x0019fd0c, 0x001ac3c4, 0x001b966b, 0x001c762a, 0x001d643f, 
	0x001e6214, 0x001f7157, 0x002093ce, 0x0021cbb4, 0x00231b85, 0x00248615, 0x00260eb1, 0x0027b95b, 0x00298a9e, 0x002b881b, 
	0x002db855, 0x00302371, 0x0032d32d, 0x0035d390, 0x003933e7, 0x003d072e, 0x00416643, 0x0046714b, 0x004c5315, 0x00534692, 
	0x005b9d6d, 0x0065cea5, 0x00728b6f, 0x0082ebe9, 0x0098c177, 0x00b75162, 0x00e529d7, 0x01318f6e, 0x01ca5dcc, 0x0394b7f0, 
	0x14960000, 0x999a0000, 
};
const int rayYStepDistance_lut[1442]=
{
	0x00000000, 0x00000477, 0x000008ef, 0x00000d67, 0x000011df, 0x00001658, 0x00001ad0, 0x00001f49, 0x000023c2, 0x0000283b, 
	0x00002cb5, 0x0000312f, 0x000035aa, 0x00003a25, 0x00003ea1, 0x0000431d, 0x0000479a, 0x00004c18, 0x00005097, 0x00005516, 
	0x00005996, 0x00005e17, 0x00006299, 0x0000671c, 0x00006ba0, 0x00007025, 0x000074ab, 0x00007932, 0x00007dbb, 0x00008244, 
	0x000086cf, 0x00008b5c, 0x00008fe9, 0x00009479, 0x00009909, 0x00009d9b, 0x0000a22f, 0x0000a6c4, 0x0000ab5b, 0x0000aff4, 
	0x0000b48f, 0x0000b92b, 0x0000bdc9, 0x0000c269, 0x0000c70b, 0x0000cbaf, 0x0000d055, 0x0000d4fe, 0x0000d9a8, 0x0000de55, 
	0x0000e303, 0x0000e7b5, 0x0000ec68, 0x0000f11e, 0x0000f5d7, 0x0000fa92, 0x0000ff4f, 0x00010410, 0x000108d3, 0x00010d98, 
	0x00011261, 0x0001172c, 0x00011bfa, 0x000120cc, 0x000125a0, 0x00012a78, 0x00012f52, 0x00013430, 0x00013911, 0x00013df5, 
	0x000142dd, 0x000147c8, 0x00014cb7, 0x000151aa, 0x000156a0, 0x00015b99, 0x00016097, 0x00016598, 0x00016a9e, 0x00016fa7, 
	0x000174b4, 0x000179c6, 0x00017edb, 0x000183f5, 0x00018913, 0x00018e36, 0x0001935d, 0x00019888, 0x00019db9, 0x0001a2ed, 
	0x0001a827, 0x0001ad66, 0x0001b2a9, 0x0001b7f1, 0x0001bd3f, 0x0001c292, 0x0001c7ea, 0x0001cd47, 0x0001d2a9, 0x0001d812, 
	0x0001dd7f, 0x0001e2f3, 0x0001e86c, 0x0001edeb, 0x0001f370, 0x0001f8fb, 0x0001fe8c, 0x00020423, 0x000209c1, 0x00020f65, 
	0x0002150f, 0x00021ac0, 0x00022078, 0x00022637, 0x00022bfc, 0x000231c9, 0x0002379c, 0x00023d77, 0x00024359, 0x00024943, 
	0x00024f34, 0x0002552d, 0x00025b2e, 0x00026137, 0x00026748, 0x00026d60, 0x00027382, 0x000279ab, 0x00027fdd, 0x00028618, 
	0x00028c5c, 0x000292a8, 0x000298fe, 0x00029f5d, 0x0002a5c5, 0x0002ac37, 0x0002b2b2, 0x0002b937, 0x0002bfc6, 0x0002c65f, 
	0x0002cd03, 0x0002d3b1, 0x0002da69, 0x0002e12c, 0x0002e7fa, 0x0002eed3, 0x0002f5b8, 0x0002fca8, 0x000303a3, 0x00030aaa, 
	0x000311be, 0x000318dd, 0x00032009, 0x00032741, 0x00032e86, 0x000335d8, 0x00033d38, 0x000344a4, 0x00034c1e, 0x000353a6, 
	0x00035b3c, 0x000362e1, 0x00036a94, 0x00037255, 0x00037a26, 0x00038206, 0x000389f5, 0x000391f4, 0x00039a03, 0x0003a222, 
	0x0003aa52, 0x0003b293, 0x0003bae5, 0x0003c348, 0x0003cbbd, 0x0003d444, 0x0003dcdd, 0x0003e589, 0x0003ee48, 0x0003f71a, 
	0x00040000, 0x000408f9, 0x00041207, 0x00041b2a, 0x00042462, 0x00042daf, 0x00043712, 0x0004408b, 0x00044a1b, 0x000453c1, 
	0x00045d80, 0x00046756, 0x00047144, 0x00047b4b, 0x0004856b, 0x00048fa5, 0x000499fa, 0x0004a469, 0x0004aef3, 0x0004b999, 
	0x0004c45b, 0x0004cf39, 0x0004da36, 0x0004e550, 0x0004f088, 0x0004fbe0, 0x00050758, 0x000512f0, 0x00051ea9, 0x00052a83, 
	0x00053680, 0x000542a0, 0x00054ee4, 0x00055b4d, 0x000567db, 0x0005748f, 0x0005816a, 0x00058e6d, 0x00059b98, 0x0005a8ed, 
	0x0005b66c, 0x0005c417, 0x0005d1ed, 0x0005dff2, 0x0005ee24, 0x0005fc86, 0x00060b18, 0x000619dc, 0x000628d2, 0x000637fc, 
	0x0006475b, 0x000656f1, 0x000666be, 0x000676c3, 0x00068704, 0x0006977f, 0x0006a838, 0x0006b930, 0x0006ca68, 0x0006dbe1, 
	0x0006ed9e, 0x0006ffa0, 0x000711e9, 0x0007247b, 0x00073758, 0x00074a81, 0x00075df9, 0x000771c1, 0x000785dd, 0x00079a4d, 
	0x0007af15, 0x0007c438, 0x0007d9b6, 0x0007ef94, 0x000805d3, 0x00081c77, 0x00083382, 0x00084af8, 0x000862dc, 0x00087b30, 
	0x000893f9, 0x0008ad3a, 0x0008c6f6, 0x0008e132, 0x0008fbf1, 0x00091737, 0x0009330a, 0x00094f6c, 0x00096c64, 0x000989f6, 
	0x0009a827, 0x0009c6fd, 0x0009e67d, 0x000a06ad, 0x000a2793, 0x000a4936, 0x000a6b9c, 0x000a8ecd, 0x000ab2d0, 0x000ad7ac, 
	0x000afd6b, 0x000b2413, 0x000b4bb0, 0x000b7449, 0x000b9de9, 0x000bc89b, 0x000bf46a, 0x000c2160, 0x000c4f8c, 0x000c7ef9, 
	0x000cafb6, 0x000ce1d1, 0x000d155a, 0x000d4a61, 0x000d80f7, 0x000db92f, 0x000df31d, 0x000e2ed4, 0x000e6c6c, 0x000eabfd, 
	0x000eed9f, 0x000f316c, 0x000f7783, 0x000fc002, 0x00100b0a, 0x001058be, 0x0010a944, 0x0010fcc6, 0x0011536e, 0x0011ad6d, 
	0x00120af7, 0x00126c42, 0x0012d18a, 0x00133b12, 0x0013a91f, 0x00141bfe, 0x00149406, 0x00151190, 0x00159502, 0x00161ecc, 
	0x0016af65, 0x00174754, 0x0017e72f, 0x00188f98, 0x00194147, 0x0019fd09, 0x001ac3bd, 0x001b9668, 0x001c7623, 0x001d6435, 
	0x001e620e, 0x001f714d, 0x002093d0, 0x0021cbbb, 0x00231b8a, 0x00248615, 0x00260eb6, 0x0027b95e, 0x00298aa8, 0x002b881f, 
	0x002db85d, 0x00302375, 0x0032d327, 0x0035d395, 0x003933df, 0x003d073c, 0x00416643, 0x00467137, 0x004c531f, 0x00534683, 
	0x005b9d7c, 0x0065cea3, 0x00728ba0, 0x0082ebc4, 0x0098c0ea, 0x00b7511a, 0x00e52900, 0x01318f5c, 0x01ca5a6e, 0x0394bdb4, 
	0x52500000, 0x0394b900, 0x01ca5940, 0x01318ed6, 0x00e528b5, 0x00b750ea, 0x0098c0c8, 0x0082ebcd, 0x00728b8d, 0x0065ce94, 
	0x005b9d70, 0x00534679, 0x004c5317, 0x00467130, 0x0041663c, 0x003d0736, 0x003933db, 0x0035d390, 0x0032d324, 0x0030236d, 
	0x002db85a, 0x002b881c, 0x00298aa6, 0x0027b95b, 0x00260eb4, 0x00248613, 0x00231b88, 0x0021cbb9, 0x002093ce, 0x001f714b, 
	0x001e620b, 0x001d6434, 0x001c7622, 0x001b9666, 0x001ac3bc, 0x0019fd08, 0x00194148, 0x00188f98, 0x0017e72e, 0x00174753, 
	0x0016af64, 0x00161eca, 0x00159501, 0x0015118f, 0x00149405, 0x00141bfe, 0x0013a91e, 0x00133b11, 0x0012d189, 0x00126c41, 
	0x00120af7, 0x0011ad6d, 0x0011536e, 0x0010fcc5, 0x0010a944, 0x001058be, 0x00100b09, 0x000fc002, 0x000f7783, 0x000f316c, 
	0x000eed9e, 0x000eabfc, 0x000e6c6c, 0x000e2ed4, 0x000df31c, 0x000db92f, 0x000d80f7, 0x000d4a61, 0x000d155a, 0x000ce1d1, 
	0x000cafb6, 0x000c7ef9, 0x000c4f8c, 0x000c2160, 0x000bf469, 0x000bc89b, 0x000b9de9, 0x000b7449, 0x000b4baf, 0x000b2413, 
	0x000afd6a, 0x000ad7ac, 0x000ab2cf, 0x000a8ecd, 0x000a6b9c, 0x000a4936, 0x000a2793, 0x000a06ac, 0x0009e67c, 0x0009c6fd, 
	0x0009a827, 0x000989f6, 0x00096c64, 0x00094f6c, 0x00093309, 0x00091737, 0x0008fbf1, 0x0008e132, 0x0008c6f6, 0x0008ad3a, 
	0x000893f9, 0x00087b30, 0x000862dc, 0x00084af8, 0x00083382, 0x00081c77, 0x000805d3, 0x0007ef94, 0x0007d9b6, 0x0007c437, 
	0x0007af15, 0x00079a4d, 0x000785dd, 0x000771c1, 0x00075df8, 0x00074a81, 0x00073758, 0x0007247b, 0x000711ea, 0x0006ffa0, 
	0x0006ed9e, 0x0006dbe1, 0x0006ca68, 0x0006b930, 0x0006a838, 0x0006977f, 0x00068704, 0x000676c3, 0x000666be, 0x000656f1, 
	0x0006475b, 0x000637fc, 0x000628d2, 0x000619dc, 0x00060b18, 0x0005fc86, 0x0005ee24, 0x0005dff1, 0x0005d1ed, 0x0005c416, 
	0x0005b66c, 0x0005a8ed, 0x00059b98, 0x00058e6c, 0x0005816a, 0x0005748f, 0x000567db, 0x00055b4d, 0x00054ee4, 0x000542a0, 
	0x00053680, 0x00052a83, 0x00051ea9, 0x000512f0, 0x00050758, 0x0004fbe0, 0x0004f088, 0x0004e550, 0x0004da36, 0x0004cf39, 
	0x0004c45b, 0x0004b999, 0x0004aef3, 0x0004a469, 0x000499fa, 0x00048fa5, 0x0004856b, 0x00047b4b, 0x00047144, 0x00046756, 
	0x00045d7f, 0x000453c1, 0x00044a1a, 0x0004408b, 0x00043712, 0x00042daf, 0x00042462, 0x00041b2a, 0x00041207, 0x000408f9, 
	0x00040000, 0x0003f71a, 0x0003ee48, 0x0003e589, 0x0003dcdd, 0x0003d444, 0x0003cbbd, 0x0003c348, 0x0003bae5, 0x0003b293, 
	0x0003aa52, 0x0003a222, 0x00039a03, 0x000391f4, 0x000389f5, 0x00038206, 0x00037a26, 0x00037255, 0x00036a94, 0x000362e1, 
	0x00035b3c, 0x000353a6, 0x00034c1e, 0x000344a4, 0x00033d37, 0x000335d8, 0x00032e86, 0x00032741, 0x00032009, 0x000318dd, 
	0x000311be, 0x00030aaa, 0x000303a3, 0x0002fca8, 0x0002f5b8, 0x0002eed3, 0x0002e7fa, 0x0002e12c, 0x0002da69, 0x0002d3b1, 
	0x0002cd03, 0x0002c65f, 0x0002bfc6, 0x0002b937, 0x0002b2b2, 0x0002ac36, 0x0002a5c5, 0x00029f5d, 0x000298fe, 0x000292a8, 
	0x00028c5c, 0x00028618, 0x00027fdd, 0x000279ab, 0x00027382, 0x00026d60, 0x00026747, 0x00026137, 0x00025b2e, 0x0002552d, 
	0x00024f34, 0x00024943, 0x00024359, 0x00023d77, 0x0002379c, 0x000231c9, 0x00022bfc, 0x00022637, 0x00022078, 0x00021ac0, 
	0x0002150f, 0x00020f64, 0x000209c1, 0x00020423, 0x0001fe8c, 0x0001f8fb, 0x0001f370, 0x0001edeb, 0x0001e86c, 0x0001e2f3, 
	0x0001dd7f, 0x0001d811, 0x0001d2a9, 0x0001cd47, 0x0001c7ea, 0x0001c292, 0x0001bd3f, 0x0001b7f1, 0x0001b2a9, 0x0001ad66, 
	0x0001a827, 0x0001a2ed, 0x00019db9, 0x00019888, 0x0001935d, 0x00018e36, 0x00018913, 0x000183f5, 0x00017edb, 0x000179c5, 
	0x000174b4, 0x00016fa7, 0x00016a9e, 0x00016598, 0x00016097, 0x00015b99, 0x000156a0, 0x000151aa, 0x00014cb7, 0x000147c8, 
	0x000142dd, 0x00013df5, 0x00013911, 0x00013430, 0x00012f52, 0x00012a78, 0x000125a0, 0x000120cc, 0x00011bfa, 0x0001172c, 
	0x00011261, 0x00010d98, 0x000108d3, 0x00010410, 0x0000ff4f, 0x0000fa92, 0x0000f5d7, 0x0000f11e, 0x0000ec68, 0x0000e7b5, 
	0x0000e303, 0x0000de55, 0x0000d9a8, 0x0000d4fd, 0x0000d055, 0x0000cbaf, 0x0000c70b, 0x0000c269, 0x0000bdc9, 0x0000b92b, 
	0x0000b48f, 0x0000aff4, 0x0000ab5b, 0x0000a6c4, 0x0000a22f, 0x00009d9b, 0x00009909, 0x00009479, 0x00008fe9, 0x00008b5c, 
	0x000086cf, 0x00008244, 0x00007dbb, 0x00007932, 0x000074ab, 0x00007025, 0x00006ba0, 0x0000671c, 0x00006299, 0x00005e17, 
	0x00005996, 0x00005516, 0x00005097, 0x00004c18, 0x0000479a, 0x0000431d, 0x00003ea1, 0x00003a25, 0x000035aa, 0x0000312f, 
	0x00002cb5, 0x0000283b, 0x000023c2, 0x00001f49, 0x00001ad0, 0x00001658, 0x000011df, 0x00000d67, 0x000008ef, 0x00000477, 
	0x00000000, 0xfffffb89, 0xfffff711, 0xfffff299, 0xffffee21, 0xffffe9a8, 0xffffe530, 0xffffe0b7, 0xffffdc3e, 0xffffd7c5, 
	0xffffd34b, 0xffffced1, 0xffffca56, 0xffffc5db, 0xffffc15f, 0xffffbce3, 0xffffb866, 0xffffb3e8, 0xffffaf69, 0xffffaaea, 
	0xffffa66a, 0xffffa1e9, 0xffff9d67, 0xffff98e4, 0xffff9460, 0xffff8fdb, 0xffff8b55, 0xffff86ce, 0xffff8245, 0xffff7dbc, 
	0xffff7931, 0xffff74a4, 0xffff7016, 0xffff6b87, 0xffff66f7, 0xffff6265, 0xffff5dd1, 0xffff593c, 0xffff54a5, 0xffff500c, 
	0xffff4b71, 0xffff46d5, 0xffff4237, 0xffff3d97, 0xffff38f5, 0xffff3451, 0xffff2fab, 0xffff2b03, 0xffff2658, 0xffff21ab, 
	0xffff1cfd, 0xffff184b, 0xffff1398, 0xffff0ee2, 0xffff0a29, 0xffff056e, 0xffff00b1, 0xfffefbf0, 0xfffef72d, 0xfffef268, 
	0xfffeed9f, 0xfffee8d4, 0xfffee405, 0xfffedf34, 0xfffeda60, 0xfffed588, 0xfffed0ae, 0xfffecbd0, 0xfffec6ef, 0xfffec20b, 
	0xfffebd23, 0xfffeb838, 0xfffeb349, 0xfffeae56, 0xfffea960, 0xfffea467, 0xfffe9f69, 0xfffe9a68, 0xfffe9562, 0xfffe9059, 
	0xfffe8b4c, 0xfffe863a, 0xfffe8125, 0xfffe7c0b, 0xfffe76ed, 0xfffe71ca, 0xfffe6ca3, 0xfffe6778, 0xfffe6247, 0xfffe5d12, 
	0xfffe57d9, 0xfffe529a, 0xfffe4d57, 0xfffe480e, 0xfffe42c1, 0xfffe3d6e, 0xfffe3816, 0xfffe32b9, 0xfffe2d57, 0xfffe27ee, 
	0xfffe2281, 0xfffe1d0d, 0xfffe1794, 0xfffe1215, 0xfffe0c90, 0xfffe0705, 0xfffe0174, 0xfffdfbdd, 0xfffdf63f, 0xfffdf09b, 
	0xfffdeaf1, 0xfffde540, 0xfffddf88, 0xfffdd9c9, 0xfffdd404, 0xfffdce37, 0xfffdc864, 0xfffdc289, 0xfffdbca6, 0xfffdb6bd, 
	0xfffdb0cc, 0xfffdaad3, 0xfffda4d2, 0xfffd9ec9, 0xfffd98b8, 0xfffd92a0, 0xfffd8c7e, 0xfffd8655, 0xfffd8023, 0xfffd79e8, 
	0xfffd73a4, 0xfffd6d58, 0xfffd6702, 0xfffd60a3, 0xfffd5a3b, 0xfffd53c9, 0xfffd4d4e, 0xfffd46c9, 0xfffd403a, 0xfffd39a1, 
	0xfffd32fd, 0xfffd2c4f, 0xfffd2597, 0xfffd1ed4, 0xfffd1806, 0xfffd112d, 0xfffd0a48, 0xfffd0358, 0xfffcfc5d, 0xfffcf555, 
	0xfffcee42, 0xfffce723, 0xfffcdff7, 0xfffcd8bf, 0xfffcd17a, 0xfffcca28, 0xfffcc2c8, 0xfffcbb5c, 0xfffcb3e2, 0xfffcac5a, 
	0xfffca4c4, 0xfffc9d1f, 0xfffc956c, 0xfffc8dab, 0xfffc85da, 0xfffc7dfa, 0xfffc760b, 0xfffc6e0c, 0xfffc65fd, 0xfffc5dde, 
	0xfffc55ae, 0xfffc4d6d, 0xfffc451b, 0xfffc3cb8, 0xfffc3443, 0xfffc2bbc, 0xfffc2323, 0xfffc1a77, 0xfffc11b8, 0xfffc08e6, 
	0xfffc0001, 0xfffbf707, 0xfffbedf9, 0xfffbe4d6, 0xfffbdb9e, 0xfffbd251, 0xfffbc8ee, 0xfffbbf75, 0xfffbb5e5, 0xfffbac3f, 
	0xfffba280, 0xfffb98aa, 0xfffb8ebc, 0xfffb84b5, 0xfffb7a95, 0xfffb705b, 0xfffb6606, 0xfffb5b97, 0xfffb510d, 0xfffb4667, 
	0xfffb3ba5, 0xfffb30c6, 0xfffb25ca, 0xfffb1ab0, 0xfffb0f78, 0xfffb0420, 0xfffaf8a8, 0xfffaed10, 0xfffae157, 0xfffad57d, 
	0xfffac980, 0xfffabd60, 0xfffab11c, 0xfffaa4b3, 0xfffa9825, 0xfffa8b71, 0xfffa7e96, 0xfffa7194, 0xfffa6468, 0xfffa5713, 
	0xfffa4994, 0xfffa3be9, 0xfffa2e13, 0xfffa200e, 0xfffa11dc, 0xfffa037a, 0xfff9f4e8, 0xfff9e624, 0xfff9d72e, 0xfff9c804, 
	0xfff9b8a4, 0xfff9a90f, 0xfff99942, 0xfff9893c, 0xfff978fc, 0xfff96881, 0xfff957c8, 0xfff946d0, 0xfff93598, 0xfff9241f, 
	0xfff91262, 0xfff90060, 0xfff8ee16, 0xfff8db84, 0xfff8c8a8, 0xfff8b57f, 0xfff8a207, 0xfff88e3f, 0xfff87a23, 0xfff865b3, 
	0xfff850ea, 0xfff83bc8, 0xfff8264a, 0xfff8106c, 0xfff7fa2d, 0xfff7e389, 0xfff7cc7d, 0xfff7b507, 0xfff79d24, 0xfff784cf, 
	0xfff76c07, 0xfff752c6, 0xfff7390a, 0xfff71ecf, 0xfff7040f, 0xfff6e8c9, 0xfff6ccf7, 0xfff6b094, 0xfff6939c, 0xfff6760a, 
	0xfff657d9, 0xfff63903, 0xfff61983, 0xfff5f953, 0xfff5d86d, 0xfff5b6ca, 0xfff59464, 0xfff57133, 0xfff54d30, 0xfff52853, 
	0xfff50296, 0xfff4dbec, 0xfff4b451, 0xfff48bb7, 0xfff46217, 0xfff43765, 0xfff40b96, 0xfff3de9f, 0xfff3b073, 0xfff38107, 
	0xfff35049, 0xfff31e2f, 0xfff2eaa7, 0xfff2b59f, 0xfff27f08, 0xfff246d1, 0xfff20ce3, 0xfff1d12c, 0xfff19393, 0xfff15404, 
	0xfff11261, 0xfff0ce93, 0xfff0887d, 0xfff03ffd, 0xffeff4f6, 0xffefa742, 0xffef56bc, 0xffef033a, 0xffeeac90, 0xffee5292, 
	0xffedf508, 0xffed93be, 0xffed2e74, 0xffecc4ec, 0xffec56e0, 0xffebe3ff, 0xffeb6bf9, 0xffeaee6e, 0xffea6afd, 0xffe9e137, 
	0xffe9509c, 0xffe8b8ae, 0xffe818d2, 0xffe77066, 0xffe6beb9, 0xffe602f6, 0xffe53c43, 0xffe46997, 0xffe389df, 0xffe29bca, 
	0xffe19def, 0xffe08eb4, 0xffdf6c2d, 0xffde3446, 0xffdce474, 0xffdb79e4, 0xffd9f148, 0xffd8469d, 0xffd67559, 0xffd477db, 
	0xffd247a0, 0xffcfdc83, 0xffcd2cc6, 0xffca2c62, 0xffc6cc09, 0xffc2f8bf, 0xffbe99c8, 0xffb98ec2, 0xffb3acfb, 0xffacb980, 
	0xffa462aa, 0xff9a3177, 0xff8d744d, 0xff7d1445, 0xff673ec7, 0xff48aef7, 0xff1ad6b5, 0xfece6eb0, 0xfe35a466, 0xfc6b3730, 
	0xb2600000, 0xfc6b521c, 0xfe35a4b8, 0xfece71ae, 0xff1ad864, 0xff48af04, 0xff673f87, 0xff7d144b, 0xff8d74b9, 0xff9a317b, 
	0xffa462ad, 0xffacb9b9, 0xffb3acfd, 0xffb98eeb, 0xffbe99ca, 0xffc2f8c0, 0xffc6cc24, 0xffca2c63, 0xffcd2cdb, 0xffcfdc96, 
	0xffd247a1, 0xffd477ea, 0xffd67559, 0xffd846aa, 0xffd9f148, 0xffdb79ef, 0xffdce47f, 0xffde3446, 0xffdf6c36, 0xffe08eb4, 
	0xffe19df7, 0xffe29bca, 0xffe389df, 0xffe4699e, 0xffe53c43, 0xffe602fb, 0xffe6beb9, 0xffe7706b, 0xffe818d7, 0xffe8b8ae, 
	0xffe950a0, 0xffe9e137, 0xffea6afd, 0xffeaee71, 0xffeb6bfa, 0xffebe402, 0xffec56e0, 0xffecc4ef, 0xffed2e77, 0xffed93be, 
	0xffedf50a, 0xffee5292, 0xffeeac93, 0xffef033a, 0xffef56bd, 0xffefa744, 0xffeff4f7, 0xfff03fff, 0xfff0887d, 0xfff0ce95, 
	0xfff11263, 0xfff15404, 0xfff19395, 0xfff1d12c, 0xfff20ce5, 0xfff246d1, 0xfff27f0a, 0xfff2b5a1, 0xfff2eaa7, 0xfff31e2f, 
	0xfff3504a, 0xfff38107, 0xfff3b075, 0xfff3de9f, 0xfff40b97, 0xfff43765, 0xfff46217, 0xfff48bb8, 0xfff4b451, 0xfff4dbed, 
	0xfff50296, 0xfff52854, 0xfff54d31, 0xfff57133, 0xfff59465, 0xfff5b6ca, 0xfff5d86e, 0xfff5f953, 0xfff61984, 0xfff63904, 
	0xfff657d9, 0xfff6760b, 0xfff6939c, 0xfff6b094, 0xfff6ccf7, 0xfff6e8c9, 0xfff70410, 0xfff71ece, 0xfff7390a, 0xfff752c6, 
	0xfff76c07, 0xfff784d0, 0xfff79d24, 0xfff7b508, 0xfff7cc7e, 0xfff7e389, 0xfff7fa2d, 0xfff8106c, 0xfff8264a, 0xfff83bc8, 
	0xfff850eb, 0xfff865b3, 0xfff87a23, 0xfff88e3f, 0xfff8a207, 0xfff8b57f, 0xfff8c8a8, 0xfff8db85, 0xfff8ee17, 0xfff90060, 
	0xfff91262, 0xfff9241f, 0xfff93599, 0xfff946d0, 0xfff957c7, 0xfff96881, 0xfff978fd, 0xfff9893c, 0xfff99943, 0xfff9a90f, 
	0xfff9b8a5, 0xfff9c804, 0xfff9d72e, 0xfff9e625, 0xfff9f4e8, 0xfffa037a, 0xfffa11dc, 0xfffa200f, 0xfffa2e13, 0xfffa3bea, 
	0xfffa4994, 0xfffa5713, 0xfffa6468, 0xfffa7194, 0xfffa7e96, 0xfffa8b71, 0xfffa9825, 0xfffaa4b3, 0xfffab11c, 0xfffabd60, 
	0xfffac980, 0xfffad57d, 0xfffae158, 0xfffaed10, 0xfffaf8a8, 0xfffb0420, 0xfffb0f78, 0xfffb1ab0, 0xfffb25ca, 0xfffb30c7, 
	0xfffb3ba5, 0xfffb4668, 0xfffb510d, 0xfffb5b97, 0xfffb6606, 0xfffb705b, 0xfffb7a95, 0xfffb84b5, 0xfffb8ebc, 0xfffb98ab, 
	0xfffba281, 0xfffbac3f, 0xfffbb5e5, 0xfffbbf75, 0xfffbc8ef, 0xfffbd251, 0xfffbdb9f, 0xfffbe4d6, 0xfffbedf9, 0xfffbf707, 
	0xfffc0000, 0xfffc08e6, 0xfffc11b8, 0xfffc1a77, 0xfffc2323, 0xfffc2bbc, 0xfffc3443, 0xfffc3cb8, 0xfffc451b, 0xfffc4d6d, 
	0xfffc55ae, 0xfffc5dde, 0xfffc65fd, 0xfffc6e0c, 0xfffc760b, 0xfffc7dfa, 0xfffc85da, 0xfffc8dab, 0xfffc956d, 0xfffc9d1f, 
	0xfffca4c4, 0xfffcac5a, 0xfffcb3e2, 0xfffcbb5c, 0xfffcc2c9, 0xfffcca28, 0xfffcd17a, 0xfffcd8bf, 0xfffcdff7, 0xfffce723, 
	0xfffcee42, 0xfffcf555, 0xfffcfc5d, 0xfffd0358, 0xfffd0a48, 0xfffd112d, 0xfffd1806, 0xfffd1ed4, 0xfffd2597, 0xfffd2c4f, 
	0xfffd32fd, 0xfffd39a1, 0xfffd403a, 0xfffd46c9, 0xfffd4d4e, 0xfffd53c9, 0xfffd5a3b, 0xfffd60a3, 0xfffd6702, 0xfffd6d58, 
	0xfffd73a4, 0xfffd79e8, 0xfffd8023, 0xfffd8655, 0xfffd8c7e, 0xfffd92a0, 0xfffd98b8, 0xfffd9ec9, 0xfffda4d2, 0xfffdaad3, 
	0xfffdb0cc, 0xfffdb6bd, 0xfffdbca7, 0xfffdc289, 0xfffdc864, 0xfffdce37, 0xfffdd404, 0xfffdd9ca, 0xfffddf88, 0xfffde540, 
	0xfffdeaf1, 0xfffdf09c, 0xfffdf63f, 0xfffdfbdd, 0xfffe0174, 0xfffe0705, 0xfffe0c90, 0xfffe1215, 0xfffe1794, 0xfffe1d0e, 
	0xfffe2281, 0xfffe27ef, 0xfffe2d57, 0xfffe32b9, 0xfffe3817, 0xfffe3d6e, 0xfffe42c1, 0xfffe480f, 0xfffe4d57, 0xfffe529a, 
	0xfffe57d9, 0xfffe5d13, 0xfffe6248, 0xfffe6778, 0xfffe6ca3, 0xfffe71ca, 0xfffe76ed, 0xfffe7c0b, 0xfffe8125, 0xfffe863a, 
	0xfffe8b4c, 0xfffe9059, 0xfffe9562, 0xfffe9a68, 0xfffe9f69, 0xfffea467, 0xfffea960, 0xfffeae56, 0xfffeb349, 0xfffeb837, 
	0xfffebd23, 0xfffec20b, 0xfffec6ef, 0xfffecbd0, 0xfffed0ae, 0xfffed589, 0xfffeda60, 0xfffedf34, 0xfffee406, 0xfffee8d4, 
	0xfffeed9f, 0xfffef268, 0xfffef72d, 0xfffefbf1, 0xffff00b1, 0xffff056e, 0xffff0a29, 0xffff0ee2, 0xffff1398, 0xffff184b, 
	0xffff1cfd, 0xffff21ac, 0xffff2658, 0xffff2b03, 0xffff2fab, 0xffff3451, 0xffff38f5, 0xffff3d97, 0xffff4237, 0xffff46d5, 
	0xffff4b71, 0xffff500c, 0xffff54a5, 0xffff593c, 0xffff5dd1, 0xffff6265, 0xffff66f7, 0xffff6b88, 0xffff7017, 0xffff74a4, 
	0xffff7931, 0xffff7dbc, 0xffff8245, 0xffff86ce, 0xffff8b55, 0xffff8fdb, 0xffff9460, 0xffff98e4, 0xffff9d67, 0xffffa1e9, 
	0xffffa66a, 0xffffaaea, 0xffffaf69, 0xffffb3e8, 0xffffb866, 0xffffbce3, 0xffffc15f, 0xffffc5db, 0xffffca56, 0xffffced1, 
	0xffffd34b, 0xffffd7c5, 0xffffdc3e, 0xffffe0b7, 0xffffe530, 0xffffe9a9, 0xffffee21, 0xfffff299, 0xfffff711, 0xfffffb89, 
	0x00000000, 0x999a0000, 
};
