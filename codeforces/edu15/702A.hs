import Data.Maybe
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

-- ID:	702A (Maximum Increase)
-- URL:	http://codeforces.com/contest/702/problem/A

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	n <- getInt
	xs <- getInts
	print $ solve xs

solve (x:xs) = f xs x 1 1 where
	f [] prev cnt maxCnt = max cnt maxCnt
	f (curr:xs) prev cnt maxCnt
		| curr > prev = f xs curr (cnt+1) maxCnt
		| otherwise = f xs curr 1 (max cnt maxCnt)
