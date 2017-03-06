-- Codeforces Round #403 (Div. 2)
-- B. The Meeting Place Cannot Be Changed
-- http://codeforces.com/contest/782/problem/B

import Control.Monad
import Data.Maybe
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map parseInt . BS8.words) `fmap` BS.getLine :: IO [Int]
parseInt = fst . fromJust . BS8.readInt

main = do
	n <- getInt
	coords <- (map fromIntegral) `fmap` getInts :: IO [Double]
	speeds <- (map fromIntegral) `fmap` getInts :: IO [Double]
	let (lb, ub) = recurse coords speeds (0.0, 1e9) 100
	let answer = (lb + ub) / 2.0
	print answer

recurse _ _ result 0 = result
recurse coords speeds (lb, ub) cnt
	| canMeet coords speeds mid = recurse coords speeds (lb, mid) (cnt-1)
	| otherwise = recurse coords speeds (mid, ub) (cnt-1)
	where mid = (lb + ub) / 2.0

canMeet :: [Double] -> [Double] -> Double -> Bool
canMeet coords speeds t = isJust $ foldl getOverlap (Just (0.0, 1e9)) ranges where
	ranges = zipWith (\coord speed -> (coord - speed * t, coord + speed * t)) coords speeds

getOverlap Nothing _ = Nothing
getOverlap (Just (l1, r1)) (l2, r2)
	| l > r = Nothing
	| otherwise = Just (l, r)
	where
		l = max l1 l2
		r = min r1 r2
