import Control.Monad
import Data.Maybe
import Data.Array
import Data.Int
import Data.Char
import Numeric
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

type State = Array Int64 (Int64, Int64, Int64)

toBinary :: Int64 -> String
toBinary x = showIntAtBase 2 intToDigit x ""

main = do
	[n,k] <- (map read . words) `fmap` getLine :: IO [Int64]
	let pos = toBinary k
	nexts <- listArray (0,n-1) `fmap` getInts :: IO (Array Int64 Int)
	costs <- listArray (0,n-1) `fmap` getInts :: IO (Array Int64 Int)
	let state0 = initState n nexts costs
	let states = scanl (step n) state0 [1..length pos-1]
	let valids = pos `seq` fst $ unzip $ filter valid (zip states (reverse pos))
	let soln = findSoln valids n
	-- printing solutions seems not the problem
	forM_ soln $ \(_, si, mi) -> do
		putStr (show si)
		putChar ' '
		putStrLn (show mi)

--findSoln :: [State] -> Int64 -> [(Int64,Int64,Int64)]
findSoln :: [State] -> Int64 -> Array Int64 (Int64,Int64,Int64)
findSoln states n = f states $ listArray (0,n-1) [(i,0,10^8+1) | i <- [0..n-1]] where
	f [] soln = soln
	f (st:states) curr = f states $ listArray (0,n-1) [(to1,s+len1, min m min1) | i <- [0..n-1], let (to,s,m) = curr ! i, let (to1,len1,min1) = st ! to]
	--f (st:states) curr = f states [(to1,s+len1, min m min1) | (i,s,m) <- curr, let (to1,len1,min1)=st!i]

valid (state, digit) = digit == '1'

initState :: Int64 -> Array Int64 Int -> Array Int64 Int -> State
initState n nexts costs = listArray (0,n-1) [(next i, cost i, cost i) | i <- [0..n-1]] where
	cost i = fromIntegral $ costs ! i
	next i = fromIntegral $ nexts ! i

step :: Int64 -> State -> Int -> State
step n state _ = listArray (0,n-1) [f i | i <- [0..n-1]]  where
	f i = (to2, len1+len2, min min1 min2) where
		(to1, len1, min1) = state ! i
		(to2, len2, min2) = state ! to1
