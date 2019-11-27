# 中途上车模型
# https://www.imaibo.net/viewpoint/detail/3053606?share_uid=4570952

num = 5
basePx = 100.0
percentSell = 5 / 100
percentBuy = percentSell * 2 / (num - 1)  # 个人臆测了这个算式.
percentBuy = 2.5 / 100
money = 100 * 10000


def adbf(f: float, sign: bool = False, aD: int = 0, bF: int = 6):
    '''
    print(adbf(3.14, False, 0, 6)) => [3.140000]
    print(adbf(3.14, False, 4, 6)) => [   3.140000]
    print(adbf(3.14,  True, 0, 6)) => [+3.140000]
    print(adbf(3.14,  True, 4, 6)) => [  +3.140000]
    '''
    srcStr = ('%' + ('+' if sign else '') + '.*f') % (bF, f)
    oldStr = ('%' + ('+' if sign else '') + 'd.') % (f)
    newStr = ('%' + ('+' if sign else '') + '*d.') % (aD, f)
    dstStr = srcStr.replace(oldStr, newStr)
    return dstStr


def stepPx(stepIdx):
    assert (1 <= stepIdx and stepIdx <= num)
    return basePx * (1 + percentBuy * (stepIdx - 1))


def stepPxSell(stepIdx):
    assert (1 <= stepIdx and stepIdx <= num)
    px = stepPx(stepIdx) * (1 - percentSell)
    px = stepPx(stepIdx) - basePx * percentSell
    return px


def stepInfo(stepIdx, stepAt):
    assert (1 <= stepIdx and stepIdx <= num)
    assert (stepIdx <= stepAt and stepAt <= num)
    pxIn = stepPx(stepIdx)
    pxOut = stepPxSell(stepAt)
    percent = (pxOut - pxIn) / pxIn
    return pxIn, pxOut, percent


def showStep(showDetail: bool = True):
    for at in range(1, num + 1, 1):
        percentSum = 0
        for idx in range(1, at + 1, 1):
            data = stepInfo(idx, at)
            percentSum += data[2]
            if showDetail:
                print('[',
                      adbf(data[0], False, 3, 4),
                      adbf(data[1], False, 3, 4),
                      adbf(data[2], True, 0, 4),
                      ']',
                      sep=',',
                      end=',')
        percentAvg1 = percentSum / at
        percentAvg2 = percentSum / num
        print('{', '%+.4f' % percentAvg1, '%+.4f' % percentAvg2, '}', sep=',')


if __name__ == '__main__':
    showStep(True)
