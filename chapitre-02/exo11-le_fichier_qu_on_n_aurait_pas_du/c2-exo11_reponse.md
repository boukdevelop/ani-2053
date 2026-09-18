> # Le fichier qu'on aurait pas dû

***Énoncé :***
Committez volontairement un fichier de dix mégaoctets dans votre dépôt d'essai. Retirez-le au commit suivant, puis mesurez la taille de .git. Concluez.
--

## Avant l'envoie du fichier `>= 10Mo`

```bash
$ du -sh .git
127K    .git
```

Pour plus de détails
```bash
$ du -h .git
53K     .git/hooks
1.0K    .git/info
6.0K    .git/logs/refs/heads
2.0K    .git/logs/refs/remotes/origin
2.0K    .git/logs/refs/remotes
8.0K    .git/logs/refs
12K     .git/logs
1.0K    .git/objects/02
1.0K    .git/objects/07
1.0K    .git/objects/11
1.0K    .git/objects/20
1.0K    .git/objects/23
1.0K    .git/objects/25
1.0K    .git/objects/32
1.0K    .git/objects/61
1.0K    .git/objects/73
1.0K    .git/objects/82
2.0K    .git/objects/a2
1.0K    .git/objects/b1
1.0K    .git/objects/b6
1.0K    .git/objects/bb
3.0K    .git/objects/bd
1.0K    .git/objects/c6
1.0K    .git/objects/cd
1.0K    .git/objects/d7
1.0K    .git/objects/d9
1.0K    .git/objects/fc
0       .git/objects/info
17K     .git/objects/pack
44K     .git/objects
3.0K    .git/refs/heads
2.0K    .git/refs/remotes/origin
2.0K    .git/refs/remotes
0       .git/refs/tags
5.0K    .git/refs
127K    .git
```

## Pendant l'envoie du fichier `>= 10Mo`

```bash
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        Bee.glb

nothing added to commit but untracked files present (use "git add" to track)

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git add Bee.glb

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git commit -m "Object 3D"
[main c0bc1e2] Object 3D
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 Bee.glb

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git push
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 4 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 15.23 MiB | 17.04 MiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/boukdevelop/cassures.git
   07abea3..c0bc1e2  main -> main

```

## Après l'envoie du fichier `>= 10Mo`

```bash
FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ du -sh .git
16M     .git
```

Pour plus de détails
```bash
$ du -h .git
53K     .git/hooks
1.0K    .git/info
4.0K    .git/logs/refs/heads
5.0K    .git/logs/refs/remotes/origin
5.0K    .git/logs/refs/remotes
9.0K    .git/logs/refs
13K     .git/logs
1.0K    .git/objects/02
2.0K    .git/objects/07
1.0K    .git/objects/11
16M     .git/objects/19
1.0K    .git/objects/20
1.0K    .git/objects/22
1.0K    .git/objects/23
1.0K    .git/objects/25
1.0K    .git/objects/32
1.0K    .git/objects/57
1.0K    .git/objects/5c
1.0K    .git/objects/61
1.0K    .git/objects/6f
2.0K    .git/objects/73
1.0K    .git/objects/82
2.0K    .git/objects/a2
1.0K    .git/objects/a3
1.0K    .git/objects/b1
1.0K    .git/objects/b6
1.0K    .git/objects/bb
3.0K    .git/objects/bd
1.0K    .git/objects/c0
1.0K    .git/objects/c6
1.0K    .git/objects/cd
1.0K    .git/objects/d5
1.0K    .git/objects/d7
1.0K    .git/objects/d9
1.0K    .git/objects/fc
0       .git/objects/info
17K     .git/objects/pack
16M     .git/objects
1.0K    .git/refs/heads
2.0K    .git/refs/remotes/origin
2.0K    .git/refs/remotes
0       .git/refs/tags
3.0K    .git/refs
16M     .git
```

## Après la suppression du fichier `>= 10Mo`

```bash
$ ls
Bee.glb  feature1.txt  feature2.txt  file.txt  hello.dart  main.txt  top.cpp

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ rm Bee.glb

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add/rm <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        deleted:    Bee.glb

no changes added to commit (use "git add" and/or "git commit -a")

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git add -A

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git commit -m "Suppression du fichier 3D"
[main b070811] Suppression du fichier 3D
 1 file changed, 0 insertions(+), 0 deletions(-)
 delete mode 100644 Bee.glb

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git push
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (2/2), 237 bytes | 237.00 KiB/s, done.
Total 2 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/boukdevelop/cassures.git
   c0bc1e2..b070811  main -> main
```

---

```bash
$ du -sh .git
16M     .git
```

> ***REMARQUE :*** On remarque très clairement que .git n'a pas changer de taille après la suppression du fichier lourd, car il est toujours présent dans l'historique de mon dépôt (les fichiers compressés.)