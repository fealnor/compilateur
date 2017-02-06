entier $tab[10];
main()
entier $max, entier $i, entier $x[10];
{
 tantque ($i < 10) faire
 {
  $tab[$i] = $i;
  $i = $i + 1;
 }
 $max = $tab[0];
 $i = 1;
 tantque ($i < 10) faire
 {
  si ($max < $tab[$i]) alors 
  {
   $max = $tab[$i];
  }
  $i = $i + 1; 
 }
 ecrire($max);
}
