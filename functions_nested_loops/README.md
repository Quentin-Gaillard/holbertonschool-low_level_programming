Readme.md du dossier functions_nested_loops
mise en place d'un header, ici main.h, qui est la déclaration d'une fonction personnalisée. Elle permet d'afficher un seul caractère sur votre terminal, tout comme le ferait la fonction stardard 'putchar'

int _putchar(char c);

int (Type de retour) : C'est ce que la fonction renvoie une fois qu'elle a fini son travail. En C, les fonctions d'affichage renvoient généralement un entier (int) correspondant au code ASCII du caractère affiché si tout s'est bien passé, ou -1 (EOF) en cas d'erreur.

_putchar (Nom de la fonction) : C'est le nom de la fonction. Le tiret du bas _ au début permet de la différencier de la fonction officielle putchar de la bibliothèque standard (que le projet vous interdit d'utiliser).

(char c) (Paramètre ou Argument) : C'est ce que vous devez donner à la fonction pour qu'elle fonctionne. Ici, elle réclame une variable de type caractère (char) qu'elle nomme temporairement c. C'est le caractère qui sera imprimé à l'écran (par exemple _putchar('A');).

; (Le point-virgule) : Il est obligatoire à la fin d'un prototype. Il indique au compilateur qu'il s'agit d'une simple annonce (une déclaration) et non pas du code de la fonction (la définition).