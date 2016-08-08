import Data.List

coprimes n = map f [1..n] where
	f i = [j | j <- [1..n], gcd i j == 1]

coprime i j = gcd i j == 1

getInt = read `fmap` getLine :: IO Int

xor True True = True
xor False False = True
xor _ _ = False

diff ns xs = f ns xs [] where
	f ns [] ys = ns ++ ys
	f [] _ ys = ys
	f (n:ns) (x:xs) ys
		| n /= x = f ns (x:xs) (n:ys)
		| otherwise = f ns xs ys

main = do
	n <- getInt
	assigns <- zip [1..n] `fmap` (map read . words) `fmap` getLine :: IO [(Int,Int)]
	let assigns' = filter (\(i,x) -> x /= 0) assigns
	let cands = diff [1..n] (sort $ map snd assigns')
	if cands == []
	then
		if and [coprime x y `xor` coprime i j | (i,x) <- assigns', (j,y) <- assigns', i < j]
		then print 1
		else print 0
	else do
		print $ length (assignments n cands assigns')

--	mapM_ print (assignments n cands (coprimes n) assigns')
--	print $ length (assignments n cands (coprimes n) assigns')

assignments n ns assigns = f ns assigns where
	f [] assigns = return assigns
	f (x:xs) assigns = do
		px <- possibles x n assigns
		soln <- f xs (px:assigns)
		return soln

possibles x n assigns = [(i,x) | i <- [1..n], test i] where
	test i = all (\(j,y) -> i /= j && (coprime x y `xor` coprime i j)) assigns
