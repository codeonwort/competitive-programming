import Control.Monad
import Data.List
import Data.Maybe
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

-- ID:	GREEDYAINTA
-- URL:	https://algospot.com/judge/problem/read/GREEDYAINTA

getInt = read `fmap` getLine :: IO Int

main = do
	n <- getInt
	replicateM_ n solve

solve = do
	getInt
	ns <- BS.getLine
	let candies = (map (fst . fromJust . BS8.readInt) . BS8.words) ns
	if feasible (reverse $ tail candies)
	then putStrLn "POSSIBLE"
	else putStrLn "IMPOSSIBLE"

feasible candies = f (length candies) candies 0 where
	f _ [] _ = True
	f i (x:xs) acc
		| (x+acc) `mod` i /= 0 = False
		| otherwise = f (i-1) xs (acc + div (acc + x) i)
