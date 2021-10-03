#ifndef TESTS_H
#define TESTS_H

void assertDoubleEquals(double expected, double actual);

// PaperSheet tests

void testPaperSheetDefaultConstructor();
void testPaperSheetParametrizedConstructor(double x, double y, double thickness, double width, double height);
void testPaperSheetCopyConstructor(double x, double y, double thickness, double width, double height);
void testPaperSheetModificators();
void testPaperSheetClass();

// PaperPaperPlate tests

void testPaperPlateDefaultConstructor();
void testPaperPlateParametrizedConstructor(double x, double y, double thickness, double radius);
void testPaperPlateCopyConstructor(double x, double y, double thickness, double radius);
void testPaperPlateModificators();
void testPaperPlateClass();

// PaperStack tests

void testPaperStackClass();

// run all tests

void testAllClasses();

#endif // TESTS_H
