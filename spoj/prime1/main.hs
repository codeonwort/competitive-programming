import Control.Monad
import Data.List

-- ID:	PRIME1 (Prime Generator)
-- URL:	http://www.spoj.com/problems/PRIME1/

getInt = read `fmap` getLine :: IO Int

isqrt = floor . sqrt . fromIntegral
minus (x:xs) (y:ys) = case compare x y of
	LT -> x : minus xs (y:ys)
	EQ -> minus xs ys
	GT -> minus (x:xs) ys
minus xs _ = xs

{-
primes :: Int -> [Int]
primes 1 = []
primes m = f [2] [3,5..m] where
	f ps [] = ps
	f ps (x:xs) = f (x:ps) (minus xs [x*x, x*x+x .. m])
	{-	if all (\p -> x `mod` p /= 0) (dropWhile (> isqrt x) ps)
		then f (x:ps) xs --(minus xs $ reverse [x,2*x..m])
		else f ps xs-}
-}

primes m = 2 : f [3,5..m] where
	f [] = []
	f (p:xs)
		| p*p > m = p : xs
		| True = p : f (xs `minus` [p*p, p*p+2*p..])

pcount m n = length $ takeWhile (< m) (primes n)

isprime n ps
	| n == 1 = False
	| n == 2 = True
	| n `mod` 2 == 0 = False
	| otherwise = all (\p -> p >= n || n `mod` p /= 0) ps

main = do
	numCases <- getInt
	replicateM_ numCases $ do
		[m, n] <- fmap (map read) (words `fmap` getLine) :: IO [Int]
		let divs = primes (isqrt n)
		let ps = filter (\x -> isprime x divs) [m..n]
		forM_ ps (\p -> print p)
