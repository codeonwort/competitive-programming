import Control.Monad
import Data.Array
import Data.List

getInt = read `fmap` getLine :: IO Int
getInts = (map read . words) `fmap` getLine :: IO [Int]

main = do
	n <- getInt
	replicateM_ n solve

solve = do
	[n,m] <- getInts
	rel <- mkPair `fmap` getInts :: IO [(Int,Int)]
	let friends = accumArray (||) False ((0,0),(n-1,n-1))
					([(pair, True) | pair <- rel] ++ [((y,x),True) | (x,y) <- rel])
	print $ length (count n friends)

mkPair [] = []
mkPair (x:y:xs) = (x,y) : mkPair xs

count n friends = f [0..n-1] n where
	f ns 0 = return []
	f ns n = do
		let i = head ns
		j <- (tail ns)
		let ns' = delete j (tail ns)
		guard (friends ! (i,j))
		rest <- f ns' (n-2)
		return $ (i,j):rest
