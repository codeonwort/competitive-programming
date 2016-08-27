import Data.Maybe
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

-- ID:	703A (Mishka and Game)
-- URL:	http://codeforces.com/contest/703/problem/A

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	n <- getInt
	dices <- replicateM n getInts
	let (x,y) = solve dices
	if x == y
	then putStrLn "Friendship is magic!^^"
	else if x > y
	then putStrLn "Mishka"
	else putStrLn "Chris"

solve ds = f ds (0,0) where
	f [] res = res
	f ([d1,d2]:ds) (x,y) = f ds (x',y') where
		x' = if d1 > d2 then x+1 else x
		y' = if d2 > d1 then y+1 else y
