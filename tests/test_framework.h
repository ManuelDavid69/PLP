#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

void test_verifier_bool(const char *fichier, int ligne, const char *texte, int condition);
void test_verifier_int(const char *fichier, int ligne, const char *texte,
                       long long attendu, long long obtenu);
void test_verifier_double(const char *fichier, int ligne, const char *texte,
                          double attendu, double obtenu, double tolerance);
void test_verifier_chaine(const char *fichier, int ligne, const char *texte,
                          const char *attendu, const char *obtenu);

#define VERIFIER(condition) \
    test_verifier_bool(__FILE__, __LINE__, #condition, (condition))

#define VERIFIER_INT(attendu, obtenu) \
    test_verifier_int(__FILE__, __LINE__, #attendu " == " #obtenu, \
                      (long long)(attendu), (long long)(obtenu))

#define VERIFIER_DOUBLE(attendu, obtenu, tolerance) \
    test_verifier_double(__FILE__, __LINE__, #attendu " ~= " #obtenu, \
                         (double)(attendu), (double)(obtenu), (double)(tolerance))

#define VERIFIER_CHAINE(attendu, obtenu) \
    test_verifier_chaine(__FILE__, __LINE__, #attendu " == " #obtenu, \
                         (attendu), (obtenu))

#endif
