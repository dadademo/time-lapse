import fetch from '@/utils/fetch'
/**
 * 
 * @param {startTimestamp,endTimestamp,pageIndex,pageSize} query 
 * @returns 
 */
export function getlastImg() {
    return fetch({
        url: '/sendVideo/latest-image',
        method: 'get',
    })
}
export function getVideo() {
    return fetch({
        url: '/sendVideo/initVideo',
        method: 'get',
    })
}
