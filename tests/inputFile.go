//Program3:Pracesretezciavestavenymifunkcemi
/* kek */
package main

func newFnc(in int) int {
	i1 := 5
}

func main() {
	s1 := "Totojenejakytext"
	s2 := s1 + ",kteryjestetrochuobohatime"
	print(s1, "\n", s2)
	s1len := 0
	s1len = len(s1)
	s1len = s1len - 4
	s1, _ = substr(s2, s1len, 4)
	s1len = s1len + 1
	print("4znakyod", s1len, ".znakuv\"", s2, "\":", s1, "\n")
	print("Zadejteserazenouposloupnostvsechmalychpismena-h,")
	print("pricemzsepismenanesmejivposloupnostiopakovat:")
	err := 0
	s1, err = inputs()
	if err != 1 {
		for s1 != "abcdefgh" {
			print("\n", "Spatnezadanaposloupnost,zkusteznovu:")
			s1, _ = inputs()
		}
	} else {
	}
}
